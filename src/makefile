all: copy_quotes install

# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -I/usr/include/cjson
LIBS = -lcjson

# Source files
MONKEYFORTUNE_SRC = monkeyfortune.c
CJSON_SRC = ../lib/cJSON/cJSON.c
QUOTE_SRC_DIR = monkeytype-quotes

# Output binary
TARGET = monkeyfortune
INSTALL_TARGET = /usr/bin/monkeyfortune
QUOTE_TARGET_DIR = /usr/share/monkeyfortune

copy_quotes:
	@sudo mkdir -p $(QUOTE_TARGET_DIR)
	@sudo install -Dm755 $(QUOTE_SRC_DIR)/* $(QUOTE_TARGET_DIR)

# Build the target
$(TARGET): $(MONKEYFORTUNE_SRC)
	$(CC) $(CFLAGS) $(MONKEYFORTUNE_SRC) -o $(TARGET) $(LIBS)

install: $(TARGET)
	sudo install $(TARGET) $(INSTALL_TARGET)
