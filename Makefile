# This Makefile was tested with GNU Make
CC=gcc

# Use pkg-config to lookup the proper compiler and linker flags for LCM
CFLAGS=`pkg-config --cflags lcm` -O -Wall -std=gnu11 
LDFLAGS=`pkg-config --libs lcm`

UDP = udp
all: test_data 


test_data: eurecar_INTER_t.o test_data.o 
	$(CC) -o $@ $^ $(LDFLAGS) -lm

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< 

$(UDP): udp.o
	$(CC) -o $@ $^ $(CFLAGS) -lpcap

# prevent auto-generated lcm .c/.h files from being deleted
.SECONDARY : eurecar_*_t.c eurecar_*_t.h 


eurecar_%.c eurecar_%.h: ../types/INTER_t.lcm
	lcm-gen -c $<

clean:
	rm -f test_data
	rm -f *.o
	rm -f eurecar_*.c eurecar_*.h
