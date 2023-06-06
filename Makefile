CC=gcc
CFLAGS=-std=gnu99 -Wall -Wextra

traceroute: main.o icmp_send.o icmp_receive.o utils.o
	$(CC) $(CFLAGS) -o traceroute $^

clean:
	rm -rf *.o

distclean:
	rm -rf *.o traceroute