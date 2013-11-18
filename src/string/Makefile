CC:=clang++

default:all

all:test

string:string.o

string.o:string.cc
	$(CC) -c string.cc

test:string.o test.cc
	$(CC) test.cc string.o -o main

