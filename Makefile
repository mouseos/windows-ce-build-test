CC = arm-mingw32ce-gcc 
CFLAGS = -Wall

all: hello.exe

hello.exe: hello.c
	$(CC) $(CFLAGS) -o $@ $<
