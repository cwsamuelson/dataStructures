all: LinkedList

LinkedList: LinkedList.h main.c
	g++ -g -Wall -o main main.c

clean:
	rm -f
