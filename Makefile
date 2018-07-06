CC=g++
CFLAGS=-std=c++11 -g -Wall
DLL=--shared -fPIC
CWD=$(shell pwd)

build:
	$(CC) $(DLL) $(CFLAGS) Templater.cpp -o libtemplater.so
	sudo ln -sf $(CWD)/libtemplater.so /usr/local/lib/
