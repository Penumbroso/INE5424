// EPOS ARP Protocol Test Program

#include <utility/ostream.h>
#include <alarm.h>
#include <ip.h>

using namespace EPOS;

const int ITERATIONS = 10;

OStream cout;


int main()
{
    cout << "ARP Test Program" << endl;

    NIC nic;
    IP ip(&nic);
    NIC::Address self = nic.address();

    cout << "Src MAC: " << self << endl;
    cout << "Src IP: " << ip.address() << endl;

    if(self[5] % 2) { // sender
        cout << "Sender:" << endl;

        IP::Address dst_ip = ip.address();
        dst_ip[3]--;

        NIC::Address dst_mac;
        for(int i = 0; i < ITERATIONS; i++) {
            dst_mac = ip.arp(dst_ip);
            cout << "Dst IP: " << dst_ip << endl;
            cout << "Dst MAC: " << dst_mac << endl;
        }
    } else { // receiver
        cout << "Receiver:" << endl;

        for(int i = 0; i < ITERATIONS; i++) {
            Delay(1000000);
        }
    }

    NIC::Statistics stat = nic.statistics();
    cout << "Statistics\n"
        << "Tx Packets: " << stat.tx_packets << "\n"
        << "Tx Bytes:   " << stat.tx_bytes << "\n"
        << "Rx Packets: " << stat.rx_packets << "\n"
        << "Rx Bytes:   " << stat.rx_bytes << "\n";

    return stat.tx_bytes + stat.rx_bytes;
}
