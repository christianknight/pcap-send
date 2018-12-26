src = $(wildcard *.c)
obj = $(src:.c=.o)

CC = gcc
CFLAGS = -Wall
LDFLAGS = -lpcap

# pcap-send: $(obj) $(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
pcap-send: gcc main.c -o pcap-send -lpcap -Wall

.PHONY: clean
clean: rm -f $(obj) pcap-send