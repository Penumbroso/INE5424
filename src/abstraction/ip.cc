// EPOS IP Protocol Implementation

#include <utility/string.h>
#include <arp.h>
#include <ip.h>

__BEGIN_SYS

// Class attributes
unsigned short IP::Header::_next_id = 0;
IP::Router IP::_router;


// Methods
void IP::config_by_info()
{
    _address = System::info()->bm.node_id;

    if(!_address)
        db<IP>(WRN) << "IP::config_by_info: no valid address found in System_Info!" << endl;
}

void IP::config_by_dhcp()
{
}


IP::~IP()
{
}


IP::Buffer * IP::alloc(const Address & to, const Protocol & prot, unsigned int once, unsigned int payload)
{
    db<IP>(TRC) << "IP::alloc(to=" << to << ",prot=" << prot << ",on=" << once<< ",pl=" << payload << ")" << endl;

    Route * through = _router.search(to);
    IP * ip = through->ip();
    NIC * nic = through->nic();

    MAC_Address mac = through->arp()->resolve((through->gateway() == through->ip()->address()) ? to : through->gateway());
    if(!mac) {
         db<IP>(WRN) << "IP::alloc: destination host (" << to << ") unreachable!" << endl;
         return 0;
    }

    Buffer * pool = nic->alloc(nic, mac, NIC::IP, once, sizeof(IP::Header), payload);

    Header header(ip->address(), to, prot, 0); // length will be defined latter for each fragment

    unsigned int offset = 0;
    for(Buffer::Element * el = pool->link(); el; el = el->next()) {
        Packet * packet = el->object()->frame()->data<Packet>();

        // Setup header
        memcpy(packet->header(), &header, sizeof(Header));
        packet->flags(el->next() ? Header::MF : 0);
        packet->length(el->object()->size());
        packet->offset(offset);
        packet->header()->sum();
        db<IP>(INF) << "IP::alloc:pkt=" << packet << " => " << *packet << endl;

        offset += MAX_FRAGMENT;
    }

    return pool;
}


int IP::send(Buffer * buf)
{
    db<IP>(TRC) << "IP::send(buf=" << buf << ")" << endl;

    return buf->nic()->send(buf); // implicitly releases the pool
}


unsigned short IP::checksum(const void * data, unsigned int size)
{
    db<IP>(TRC) << "IP::checksum(d=" << data << ",s=" << size << ")" << endl;

    const unsigned char * ptr = reinterpret_cast<const unsigned char *>(data);
    unsigned long sum = 0;

    for(unsigned int i = 0; i < size - 1; i += 2)
        sum += (ptr[i] << 8) | ptr[i+1];

    if(size & 1)
        sum += ptr[size - 1];

    while(sum >> 16)
        sum = (sum & 0xffff) + (sum >> 16);

    return ~sum;
}

__END_SYS
