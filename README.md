# pcap-send

Program to send an empty (all 0's) Ethernet II packet using the libpcap "pcap_sendpacket()" function.

## Building

Compile with "gcc main.c -o pcap-send -lpcap -Wall".

## Running

Run with "sudo ./pcap-send <interface_name> <packet_length>", where <interface_name> is the name of the network adapter to send on, and <packet_length> is the length of the Ethernet frame to send in bytes (must be less than or equal to 1500). If no <packet_length> argument is give, the default length will be 1500 bytes.

Note: there needs to be an active link on the adapter being used (i.e. a device plugged connected) to be able to see the sent packets using Wireshark or tcpdump.