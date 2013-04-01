all: LinkedList

default: LinkedList

LinkedList: LinkedList.h main.c
	g++  -Wall -o main main.c

debug: LinkedList.h main.c
	g++ -DDEBUG -g -Wall -o main main.c

clean:
	rm -f main
