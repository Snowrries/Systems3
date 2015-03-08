CC=gcc
CCFLAGS= -Wall -g
OBJECTS = Main.o Node.o sorted-list.o

all:  $(OBJECTS)
	ar -rcs libsl.a Node.o sorted-list.o
	$(CC)  Main.o -L. libsl.a  -o sl

Main.o: Main.c 
	$(CC) $(CCFLAGS) -c Main.c

Node.o: Node.c Node.h
	$(CC) $(CCFLAGS) -c Node.c

sorted-list.o: sorted-list.c sorted-list.h
	$(CC) $(CCFLAGS) -c sorted-list.c

.PHONY : clean
clean:
	rm -f *.o
	rm sl
	rm libsl.a
