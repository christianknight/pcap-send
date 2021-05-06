default:
	gcc main.c -o pcap-send -lpcap -Wall

clean:
	-rm -f pcap-send