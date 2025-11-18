.PHONY: build all clean

default: all

CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lSDL3 -lX11

TARGET = clean.elf
SRC = clean.c

default: all

build:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm $(TARGET)

all: build
