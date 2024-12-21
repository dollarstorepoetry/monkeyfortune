# Compiler and flags
CC = gcc
CFLAGS = -I../lib/cJSON -g -Wall

# Source files
MONKEYFORTUNE_SRC = monkeyfortune.c
CJSON_SRC = ../lib/cJSON/cJSON.c

# Output binary
TARGET = monkeyfortune

# Build the target
$(TARGET): $(MONKEYFORTUNE_SRC) $(CJSON_SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(MONKEYFORTUNE_SRC) $(CJSON_SRC)

# Clean build artifacts
clean:
	rm -f $(TARGET)
