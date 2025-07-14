CC = gcc
CFLAGS = -Wall -I./src
SRC = src/main.c src/conf_asst.c src/config.c src/loader.c src/conv_tts.c

all:
	$(CC) $(CFLAGS) -o bin/main $(SRC)

clean:
	rm -f bin/*
