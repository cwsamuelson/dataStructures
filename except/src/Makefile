CC:=g++

default:main

lib:static

static:libexcept.a
dynamic:libexcept.so
dyn:dynamic
dynamic:libexcept.so

main:libexcept.a test.o
	$(CC) test.o -L/usr/local/lib/Jing/ -lexcept -o main

except.o:except.cc
	$(CC) -c except.cc

test.o:test.cc
	$(CC) -c test.cc

libexcept.a:except.o
	ar rcs libexcept.a except.o

dynexcept.o:except.cc
	$(CC) -fPIC -c except.cc -o dynexcept.o

libexcept.so:dynexcept.o
	$(CC) -shared -fPIC -Wl,-soname,libexcept.so.1 -o libexcept.so.1.0 dynexcept.o -lc

clean:
	rm *.o core main

cleanlib:
	rm libexcept.a

