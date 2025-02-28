# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=gnu11 -I./include
LDFLAGS =

# Debug flags (use make DEBUG=1 for debug build)
ifdef DEBUG
    CFLAGS += -g -O0 -DDEBUG
else
    CFLAGS += -O2
endif

# Directories
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
INCLUDE_DIR = include
ASSETS_DIR = assets

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c) \
       $(wildcard $(SRC_DIR)/core/*.c) \
	   $(wildcard $(SRC_DIR)/core/ui/cli/*.c) \
       $(wildcard $(SRC_DIR)/utils/*.c)

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Binary name
TARGET = $(BIN_DIR)/self-rpg

# Ensure the build directory structure exists
$(shell mkdir -p $(dir $(OBJS)) $(BIN_DIR))

# Main target
all: $(TARGET) copy-assets

# Linking
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Copy assets to build directory
copy-assets:
	@if [ -d "$(ASSETS_DIR)" ]; then \
		mkdir -p $(BUILD_DIR)/$(ASSETS_DIR); \
		cp -r $(ASSETS_DIR)/* $(BUILD_DIR)/$(ASSETS_DIR)/; \
		echo "Assets copied to $(BUILD_DIR)/$(ASSETS_DIR)"; \
	else \
		echo "Assets directory not found"; \
	fi

# Clean
clean:
	rm -rf $(BUILD_DIR)

# Install (adjust PREFIX as needed)
PREFIX = /usr/local
install: $(TARGET)
	install -d $(DESTDIR)$(PREFIX)/bin
	install $(TARGET) $(DESTDIR)$(PREFIX)/bin/

# Phony targets
.PHONY: all clean install copy-assets debug help

# Debug target
debug:
	$(MAKE) DEBUG=1

# Help target
help:
	@echo "Available targets:"
	@echo "  all     : Build the project and copy assets (default)"
	@echo "  debug   : Build with debug flags"
	@echo "  clean   : Remove build files"
	@echo "  install : Install the program"
	@echo "  help    : Show this help message"
