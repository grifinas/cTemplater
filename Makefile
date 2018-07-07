CC=g++
CFLAGS=-std=c++11 -g -Wall -O0
DLL=--shared -fPIC
CWD=$(shell pwd)

build:
	$(CC) $(DLL) $(CFLAGS) Templater.cpp -o libtemplater.so
	sudo ln -sf $(CWD)/libtemplater.so /usr/local/lib/
	sudo ldconfig

ctest:
	$(CC) $(CFLAGS) test.cpp Templater.cpp

test: build
	$(CC) $(CFLAGS) test.cpp -L/usr/local/lib -ltemplater
	./a.out
