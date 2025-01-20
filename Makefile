CC = arm-mingw32ce-g++
CFLAGS = -Wall -shared
TARGET = exe_launcher.dll
OBJS = exe_launcher.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

exe_launcher.o: exe_launcher.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS)
