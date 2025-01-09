all: copy_quotes build

# do a silly thing first
QUOTE_TARGET_DIR = /usr/share/monkeyfortune
QUOTE_SRC_DIR = monkeytype-quotes
copy_quotes:
	@sudo mkdir -p $(QUOTE_TARGET_DIR)
	@sudo chmod 755 $(QUOTE_TARGET_DIR)
	@sudo install -Dm755 $(QUOTE_SRC_DIR)/* $(QUOTE_TARGET_DIR)

# Compiler and flags
CC = gcc
CFLAGS = -g -I../lib/cJSON -Wall

# Source files
MONKEYFORTUNE_SRC = monkeyfortune.c
CJSON_SRC = ../lib/cJSON/cJSON.c

# Output binary
TARGET = monkeyfortune
INSTALL_TARGET = /usr/bin/monkeyfortune

# Build the target
# $(TARGET): $(MONKEYFORTUNE_SRC) $(CJSON_SRC)
build:
	$(CC) $(CFLAGS) $(MONKEYFORTUNE_SRC) $(CJSON_SRC) -o $(TARGET)
	sudo install $(TARGET) $(INSTALL_TARGET)
