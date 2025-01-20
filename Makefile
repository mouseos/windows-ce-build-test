CC = arm-mingw32ce-g++ 
CFLAGS = -Wall

all: hello.exe

hello.exe: hello.c
	$(CC) $(CFLAGS) -o $@ $<
