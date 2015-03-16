CC=gcc
CCFLAGS= -Wall -g -Werror 
OBJECTS = Node.o sorted-list.o RadixTree.o indexer.o tokenizer.o

all:  $(OBJECTS) main.o
	ar -rcs libygg.a $(OBJECTS)
	$(CC)  main.o -L. libygg.a  -o index

main.o: main.c 
	$(CC) $(CCFLAGS) -c main.c

Node.o: Node.c Node.h
	$(CC) $(CCFLAGS) -c Node.c

sorted-list.o: sorted-list.c sorted-list.h
	$(CC) $(CCFLAGS) -c sorted-list.c

RadixTree.o: RadixTree.c RadixTree.h
	$(CC) $(CCFLAGS) -c RadixTree.c

tokenizer.o: tokenizer.c tokenizer.h
	$(CC) $(CCFLAGS) -c tokenizer.c

indexer.o: indexer.c indexer.h
	$(CC) $(CCFLAGS) -c indexer.c


.PHONY : clean
clean:
	rm -f *.o
	rm index
	rm libygg.a
