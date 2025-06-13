# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -Werror -std=c11
INCLUDES = -Iinclude

# Source and target definitions
SRC_DIR = src
OBJ_DIR = obj
BIN = snakes

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

# Default target: build the binary
all: $(BIN)

# Link all object files to create the binary
$(BIN): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

# Compile each source file into an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create the object directory if it does not exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Remove all build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN)

# Clean and rebuild everything
rebuild: clean all
