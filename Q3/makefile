# compiler variables
CC = gcc
CFLAGS = -Wall -O2
LDLIBS = -lm

# custom variables
objects = my_grep.o

my_grep : $(objects)
	$(CC) -o $@ $(objects) $(LDLIBS) $(CFLAGS) 

my_grep.o : my_grep.c
	$(CC) -c $< $(CFLAGS) 
# test target

.PHONY: clean
clean:
	rm -f my_grep $(objects)

test : my_grep
	cat testfile | ./my_grep a
	cat testfile | ./my_grep hello -n
	cat testfile | ./my_grep -nc foobar
	cat testfile | ./my_grep -nvc foobar
	./my_grep hello testfile
	./my_grep a -nvc testfile
	./my_grep \n -n testfile


