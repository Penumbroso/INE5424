// EPOS IP Protocol Declarations

#ifndef __ip_h
#define __ip_h

#include <nic.h>
#include <system.h>
#include <arp.h>

__BEGIN_SYS

class IP
{
public:
    // Zero-copy Buffers
    typedef NIC::Buffer Buffer;

    template<unsigned int SIZE, unsigned int UNIT_SIZE>
    class Bitmap
    {
    public:
        Bitmap(): _size(SIZE / UNIT_SIZE) { memset(&_map, 0, SIZE / UNIT_SIZE / 8); }

        bool set(unsigned int index) {
            if(_map[index / UNIT_SIZE])
                return false;
            else {
                _map[index / UNIT_SIZE] = true;
                return true;
            }
        }

        bool reset(unsigned int index) {
            if(!_map[index / UNIT_SIZE])
                return false;
            else {
                _map[index / UNIT_SIZE] = false;
                return true;
            }
        }

        void resize(unsigned int size) {
            if(size < SIZE)
                _size = size / UNIT_SIZE;
        }

        bool full() const {
            for(unsigned int i = 0; i < _size; i++)
                if(!_map[i])
                    return false;
            return true;
        }

        bool empty() const {
            for(unsigned int i = 0; i < _size; i++)
                if(_map[i])
                    return false;
            return true;
        }

    private:
        unsigned int _size;
        bool _map[SIZE / UNIT_SIZE];
    };

public:
    static const unsigned int PROTOCOL = NIC::IP;

    // Addresses
    typedef NIC::Address MAC_Address;
    typedef NIC_Common::Address<4> Address;


    // RFC 1700 Protocols
    typedef unsigned char Protocol;
    enum {
        ICMP    = 0x01,
        TCP     = 0x06,
        UDP     = 0x11,
        RDP     = 0x1b,
        TTP     = 0x54
    };

    // IP Header
    class Header
    {
    public:
        static const unsigned int VER = 4;
        static const unsigned int IHL = 5; // 20 bytes
        static const unsigned int TOS = 0;
        static const unsigned int TTL = Traits<IP>::TTL;

        enum {
            MF = 1, // More Fragments
            DF = 2  // Don't Fragment
        };

    public:
        Header() {}
        Header(const Address & from, const Address & to, const Protocol & prot, unsigned int size) :
            _ihl(IHL), _version(VER), _tos(TOS), _length(htons(size)), _id(htons(_next_id++)),
            _offset(0), _flags(0), _ttl(TTL), _protocol(prot), _checksum(0), _from(from), _to(to) {}

        unsigned short length() const { return ntohs(_length); }
        void length(unsigned short length) { _length = htons(length); }

        unsigned short id() const { return ntohs(_id); }

        // Offsets in bytes that are converted to 8-byte unities
        unsigned short offset() const { return (ntohs((_flags << 13) | _offset) & 0x1fff) << 3; }
        void offset(unsigned short off) {
            unsigned short tmp = htons((flags() << 13) | (off >> 3));
            _offset = tmp & 0x1fff;
            _flags  = tmp >> 13;
        }

        unsigned short flags() const { return ntohs((_flags << 13) | _offset) >> 13; }
        void flags(unsigned short flg) {
            unsigned short tmp = htons((flg << 13) | (offset() >> 3));
            _offset = tmp & 0x1fff;
            _flags  = tmp >> 13;
        }

        unsigned char ttl() { return _ttl; }

        const Protocol & protocol() const { return _protocol; }

        unsigned short checksum() const { return ntohs(_checksum); }

        void sum() { _checksum = 0; _checksum = htons(IP::checksum(reinterpret_cast<unsigned char *>(this), _ihl * 4)); }
        bool check() { return !IP::checksum(reinterpret_cast<unsigned char *>(this), _ihl * 4); }

        const Address & from() const { return _from; }
        void from(const Address & from){ _from = from; }

        const Address & to() const { return _to; }
        void to(const Address & to){ _to = to; }

        friend Debug & operator<<(Debug & db, const Header & h) {
            db << "{ver=" << h._version
               << ",ihl=" << h._ihl
               << ",tos=" << h._tos
               << ",len=" << h.length()
               << ",id="  << h.id()
               << ",off=" << h.offset()
               << ",flg=" << ((h.flags() & DF) ? "DF" : (h.flags() & MF) ? "MF" : "--")
               << ",ttl=" << h._ttl
               << ",pro=" << h._protocol
               << ",chk=" << hex << h._checksum << dec
               << ",from=" << h._from
               << ",to=" << h._to
               << "}";
            return db;
        }

    private:
        unsigned char   _ihl:4;         // IP Header Length (in 32-bit words)
        unsigned char   _version:4;     // IP Version
        unsigned char    _tos;          // Type Of Service (not used -> 0)
        unsigned short  _length;        // Length of datagram in bytes (header + data)
        unsigned short  _id;            // Datagram id
        unsigned short  _offset:13;     // Fragment offset (x 8 bytes)
        unsigned short  _flags:3;       // Flags (DF, MF)
        unsigned char   _ttl;           // Time To Live
        Protocol        _protocol;      // Payload Protocol (RFC 1700)
        unsigned short  _checksum;      // Header checksum (RFC 1071)
        Address         _from;          // Source IP address
        Address         _to;            // Destination IP address

        static unsigned short _next_id;
    } __attribute__((packed));


    static const unsigned int MAX_FRAGMENT = sizeof(NIC::Data) - sizeof(Header);
    static const unsigned int MTU = 65535 - sizeof(Header);
    typedef unsigned char Data[MTU];

    // IP Packet
    class Packet: public Header
    {
    public:
        Packet() {}
        Packet(const Address & from, const Address & to, const Protocol & prot, unsigned int size):
            Header(from, to, prot, size + sizeof(Header)) {}
        Packet(const Address & from, const Address & to, const Protocol & prot, const void * data, unsigned int size):
            Header(from, to, prot, size + sizeof(Header)) {
            header()->sum();
            memcpy(_data, data, size > sizeof(Data) ? sizeof(Data) : size);
        }

        Header * header() { return this; }

        template<typename T>
        T * data() { return reinterpret_cast<T *>(&_data); }

        friend Debug & operator<<(Debug & db, const Packet & p) {
            db << "{head=" << reinterpret_cast<const Header &>(p) << ",data=" << p._data << "}";
            return db;
        }

    private:
        Data _data;
    } __attribute__((packed));

    typedef Packet PDU;

public:
    IP(NIC * nic): _nic(nic), _arp(_nic, this), _address(Traits<IP>::Config<0>::ADDRESS), _netmask(Traits<IP>::Config<0>::NETMASK),
                   _broadcast((_address & _netmask) | ~_netmask), _gateway(Traits<IP>::Config<0>::GATEWAY) {
        if(Traits<IP>::Config<0>::TYPE == Traits<IP>::MAC)
            _address[sizeof(Address) -1] = _nic->address()[sizeof(MAC_Address) - 1];
    }
    ~IP();

    Buffer * alloc(const Address & to, const Protocol & prot, unsigned int once, unsigned int payload);

    int send(Buffer * buf);

    const Address & address() const { return _address; }

    MAC_Address  arp(const Address & addr) { return _arp.resolve(addr); }

    static const unsigned int mtu() { return MTU; }

    static unsigned short checksum(const void * data, unsigned int size);

private:
    void config_by_info();
    void config_by_rarp();
    void config_by_dhcp();

protected:
    NIC * _nic;
    ARP<NIC, IP> _arp;

    Address _address;
    Address _netmask;
    Address _broadcast;
    Address _gateway;
};

__END_SYS

#endif
