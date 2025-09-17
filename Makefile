PROGRAM_NAME := main

SRC_DIR := src
INC_DIR := inc
BUILD_DIR := build

CC := gcc
CC_FLAGS := -std=c99 -Wall -Os -I ./$(INC_DIR) -lm -lncurses

SOURCE_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJECT_FILES := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCE_FILES))
DEPENDENCY_FILES := $(OBJECT_FILES:.o=.d)
EXEC_FILE := $(BUILD_DIR)/$(PROGRAM_NAME)

all: $(EXEC_FILE)

# create the build directory
$(BUILD_DIR):
	mkdir -pv $(BUILD_DIR)

# check if build directory exists
$(OBJECT_FILES): | $(BUILD_DIR)

# compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -MMD -MP $(CC_FLAGS) $< -o $@

-include $(DEPENDENCY_FILES)

# link
$(EXEC_FILE): $(OBJECT_FILES)
	$(CC) $^ $(CC_FLAGS) -o $@

# run executable
run:
	./$(EXEC_FILE)

# remove build files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean
