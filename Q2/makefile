# compiler variables
CC = gcc
CFLAGS = -Wall -O2
LDLIBS = -lm

# custom variables
objects = my_seq.o

my_seq : $(objects)
	$(CC) -o $@ $(objects) $(LDLIBS) $(CFLAGS) 

my_seq.o : my_seq.c
	$(CC) -c $< $(CFLAGS) 
# test target

.PHONY: clean
clean:
	rm -f my_seq $(objects)

test : my_seq
	./my_seq 5
	./my_seq 1 10
	./my_seq -w 10 100
	./my_seq -w 10 5 100
	./my_seq -w -10 5 10
	./my_seq -w -10 5 -5
	./my_seq -w -10 -1 -15
	./my_seq -w -10 -5 -15
	./my_seq -w 0 2 -6


