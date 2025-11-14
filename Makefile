# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Source and object files
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/main_window.c $(SRC_DIR)/widgets.c
OBJECTS = $(OBJ_DIR)/main.o $(OBJ_DIR)/main_window.o $(OBJ_DIR)/widgets.o
TARGET = final

# Default target
all: $(TARGET)

# Create obj directory if needed
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Link object files into final binary
$(TARGET): $(OBJ_DIR) $(OBJECTS)
	@$(CC) $(OBJECTS) -o $(TARGET) $(LIBS)
	@echo "Compilation finished"

# Compile each .c file into .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	@rm -rf $(OBJ_DIR) $(TARGET)
	@echo "Cleaned up build files"

.PHONY: all clean
