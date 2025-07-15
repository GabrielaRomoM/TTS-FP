CC = gcc
CFLAGS = -Wall -I./src
SRC = src/main.c src/conf_asst_gpio.c src/config.c src/loader.c src/conv_tts.c

all:
	$(CC) $(CFLAGS) -o bin/main $(SRC) -lwiringPi

clean:
	rm -f bin/*
	rm tts.conf
