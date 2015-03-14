CC=gcc
CCFLAGS= -Wall -g -Werror 
OBJECTS = main.o Node.o sorted-list.o RadixTree.o indexer.o isascii.o tokenizer2.o

all:  $(OBJECTS)
	ar -rcs libsl.a $(OBJECTS)
	$(CC)  Main.o -L. libsl.a  -o sl

Main.o: main.c 
	$(CC) $(CCFLAGS) -c main.c

Node.o: Node.c Node.h
	$(CC) $(CCFLAGS) -c Node.c

sorted-list.o: sorted-list.c sorted-list.h
	$(CC) $(CCFLAGS) -c sorted-list.c

RadixTree.o: RadixTree.c RadixTree.h
	$(CC) $(CCFLAGS) -c RadixTree.c

isascii.o: isascii.c isascii.h
	$(CC) $(CCFLAGS) -c isascii.c

tokenizer2.o: tokenizer2.c tokenizer2.h
	$(CC) $(CCFLAGS) -c tokenizer2.c



.PHONY : clean
clean:
	rm -f *.o
	rm sl
	rm libsl.a
