# compiler variables
CC = gcc
CFLAGS = -Wall -O2
LDLIBS = -lm

# custom variables
objects = my_hexdump.o

my_hexdump : $(objects)
	$(CC) -o $@ $(objects) $(LDLIBS) $(CFLAGS) 

my_hexdump.o : my_hexdump.c
	$(CC) -c $< $(CFLAGS) 
# test target

.PHONY: clean
clean:
	rm -f my_hexdump $(objects)

test : my_hexdump

