# compiler variables
CC = gcc
CFLAGS = -Wall -O2
LDLIBS = -lm

# custom variables
objects = round.o

round : $(objects)
	$(CC) -o $@ $(objects) $(LDLIBS) $(CFLAGS) 

round.o : round.c
	$(CC) -c $< $(CFLAGS) 
# test target

.PHONY: clean
clean:
	rm -f round $(objects)

test : round
	./round 1000
	./round 1024
	./round 1100
	./round -M 100000
	./round -M 1048576
	./round -M 10485760
	./round -M 104857600
	./round -G 1073741824
	./round -T 1099511627776
	./round -P 1125899906842624
	./round -E 1152921504606846976
	./round -h 11529215046 


