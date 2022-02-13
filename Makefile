# Adapted from this very useful StackOverflow answer:
# https://stackoverflow.com/a/30602701
FINAL_EXE := twentyone

SRC_DIR := src
OBJ_DIR := obj

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

INCLUDE_DIR := include

CC := gcc
CFLAGS := -I$(INCLUDE_DIR) -Wall -Wextra -Werror 
DBGFLAGS := -g
LDFLAGS := -lncurses

.PHONY: all clean

all: $(FINAL_EXE)

debug: CFLAGS += -g
debug: clean $(FINAL_EXE)

$(FINAL_EXE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(FINAL_EXE)

