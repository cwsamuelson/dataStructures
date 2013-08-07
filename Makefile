all: LinkedList

default: LinkedList

LinkedList:
	make -f src/Makefile

debug:
	make -f src/Makefile debug

clean:
	make -f src/Makefile clean
