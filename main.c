/* pcap-send: sends an Ethernet II packet using the "pcap_sendpacket()" function. 
* compile: gcc main.c -o pcap-send -lpcap -Wall
* usage: sudo ./pcap-send <interface_name> <packet_length> */

#include <stdlib.h>
#include <string.h>
#include <pcap.h>

/* Data indexes for Ethernet II frame */
#define IDX_DEST_ADDRESS   0
#define IDX_SRC_ADDRESS    (IDX_DEST_ADDRESS + 6)
#define IDX_ETHERTYPE      (IDX_SRC_ADDRESS + 6)
#define IDX_PAYLOAD        (IDX_ETHERTYPE + 2)

#define HEADER_SIZE 14     /* Source/destination addresses and EtherType */

#define MAX_PACKET_SIZE 1500	// maximum Ethernet II frame size

int main(int argc, char const *argv[])
{
	printf("pcap-send\n");	// print program name

	const char *verStr;				// to hold libpcap version string
	verStr = pcap_lib_version();	// retrieve libpcap version
	printf("%s\n", verStr);			// print libpcap version

	// list out passed arguments
	printf("argc = %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    const char *interface;		// name of network interface to use
	int len;					// packet length to send, in bytes
	if (argc == 3)	{
		interface = argv[1];				// parse network interface name from arguments	
		len = strtol(argv[2], NULL, 10);	// parse packet send length from arguments
		if (len > MAX_PACKET_SIZE)	{		// check if packet length makes sense
			printf("Incorrect usage: packet length (%d) must be less than %d\n", len, MAX_PACKET_SIZE);
			return -1;
		}
	}
	else if (argc == 2)	{
		interface = argv[1];	// parse network interface name from arguments
		len = MAX_PACKET_SIZE;	// default packet send length if not given as argument
	}
	else {						// throw error - unexpected argument count
		printf("Incorrect usage: wrong number of arguments (argc = %d, expected 2 or 3)\n", argc);
		return -1;
	}

	u_char packetData[MAX_PACKET_SIZE];	// packet data buffer
	char errbuf[PCAP_ERRBUF_SIZE];		// pcap error message buffer

	memset(packetData, 0, len * sizeof(u_char));	// set entire data buffer to 0's

	memset(packetData + IDX_DEST_ADDRESS, 0xFF, 6 * sizeof(u_char));    /* Set destination to broadcast */
	memset(packetData + IDX_SRC_ADDRESS, 0xFF, 6 * sizeof(u_char));	    /* Set source to broadcast */
	packetData[IDX_ETHERTYPE] = 0x00;
	packetData[IDX_ETHERTYPE + 1] = 0x00;

	pcap_t *m_fp;	// declare the pcap struct

	// open pcap instance on the given network interface
	if ((m_fp = pcap_open_live(interface, MAX_PACKET_SIZE, 1, 300, errbuf)) == NULL) {
		printf("Bad pcap init - check adapter name & sudo permission\n");
		return -2;
	}

	// send the packet
	if (pcap_sendpacket(m_fp, packetData, (int)len) != 0)	{
		printf("Error sending packet (pcap err:%s)\n", pcap_geterr(m_fp));
		return -3;
	}

	printf("%d bytes sent on %s\n", len, interface);	// prints upon successful send
	return 0;
}