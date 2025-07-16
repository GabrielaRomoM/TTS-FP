# Makefile para pruebas TTS-FP
CC = gcc
CFLAGS = -Wall -I../src
BIN_DIR = bin
SRC_DIR = ../src

all: $(BIN_DIR)/config_test \
	$(BIN_DIR)/loader_test \
	$(BIN_DIR)/conv_tts_test \
	$(BIN_DIR)/playback_test

$(BIN_DIR)/config_test: config_test.c $(SRC_DIR)/config.c $(SRC_DIR)/conf_asst.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ -lwiringPi

$(BIN_DIR)/loader_test: loader_test.c $(SRC_DIR)/loader.c $(SRC_DIR)/config.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/conv_tts_test: conv_tts_test.c $(SRC_DIR)/conv_tts.c $(SRC_DIR)/config.c $(SRC_DIR)/loader.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/playback_test: playback_test.c $(SRC_DIR)/conv_tts.c $(SRC_DIR)/config.c $(SRC_DIR)/loader.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ -lwiringPi

clean:
	rm -rf $(BIN_DIR)
