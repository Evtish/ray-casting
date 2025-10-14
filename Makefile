PROGRAM_NAME := main

SRC_DIR := src
INC_DIR := inc
BUILD_DIR := build

CC := cc
CC_FLAGS := -MMD -MP -std=c99 -Wall -Wextra -O3 -I ./$(INC_DIR)# -save-temps=obj
LD_FLAGS := -lm

UI ?= SDL3
ifeq ($(UI),SDL3)
	CC_FLAGS += -DUSE_SDL3
	LD_FLAGS += -lSDL3
else ifeq ($(UI),NCURSES)
	CC_FLAGS += -DUSE_NCURSES
	LD_FLAGS += -lncurses
endif

SOURCE_EXTENSION := .c

SOURCE_FILES := $(wildcard $(SRC_DIR)/*$(SOURCE_EXTENSION))
OBJECT_FILES := $(patsubst $(SRC_DIR)/%$(SOURCE_EXTENSION),$(BUILD_DIR)/%.o,$(SOURCE_FILES))
DEPENDENCY_FILES := $(OBJECT_FILES:.o=.d)
EXEC_FILE := $(BUILD_DIR)/$(PROGRAM_NAME)

all: $(EXEC_FILE)

# create a build directory
$(BUILD_DIR):
	mkdir -pv $@

# check if the build directory exists
$(OBJECT_FILES): | $(BUILD_DIR)

# compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%$(SOURCE_EXTENSION)
	$(CC) -c $(CC_FLAGS) $< -o $@

-include $(DEPENDENCY_FILES)

# link
$(EXEC_FILE): $(OBJECT_FILES)
	$(CC) $^ $(CC_FLAGS) $(LD_FLAGS) -o $@

# run an executable
run: $(EXEC_FILE)
	./$(EXEC_FILE)

# remove build files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean
