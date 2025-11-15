# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude $(shell pkg-config --cflags gtk+-3.0)
LIBS = $(shell pkg-config --libs gtk+-3.0) -lsqlite3 libs/bcrypt.a

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Source and object files
SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

# Target binary
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
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Run the app
run: $(TARGET)
	@./$(TARGET) $(OBJ_DIR)/*.o

# Clean build artifacts
clean:
	@rm -rf $(OBJ_DIR) $(TARGET)
	@echo "Cleaned up build files"

.PHONY: all clean run
