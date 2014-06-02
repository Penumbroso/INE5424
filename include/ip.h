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

    // Protocol Id
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
    } __attribute__((packed));


    static const unsigned int MAX_FRAGMENT = sizeof(NIC::Data) - sizeof(Header);
    static const unsigned int MTU = 65535 - sizeof(Header);
    typedef unsigned char Data[MTU];

    // IP Packet
    class Packet: public Header
    {
    public:
        Packet() {}

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

    const Address & address() const { return _address; }

    MAC_Address  arp(const Address & addr) { return _arp.resolve(addr); }

    static const unsigned int mtu() { return MTU; }

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
