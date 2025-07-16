# === /test/Makefile ===

CC = gcc
CFLAGS = -Wall -I../src
SRC_DIR = ../src
BIN_DIR = bin

TESTS = config_test loader_test conv_tts_test playback_test

OBJS_config = $(SRC_DIR)/config.c
OBJS_loader = $(SRC_DIR)/loader.c
OBJS_conv = $(SRC_DIR)/conv_tts.c
OBJS_conf_asst = $(SRC_DIR)/conf_asst.c

.PHONY: all clean

all: $(BIN_DIR) $(TESTS)

config_test: config_test.c $(OBJS_config) $(OBJS_conf_asst)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^ -lwiringPi

loader_test: loader_test.c $(OBJS_loader) $(OBJS_config)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

conv_tts_test: conv_tts_test.c $(OBJS_conv) $(OBJS_config)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

playback_test: playback_test.c $(OBJS_conv)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^ -lwiringPi

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)
