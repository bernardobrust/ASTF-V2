PROJECT := astf_v2

CC := gcc

CERROR  := -Wall -Wextra -Werror -Walloca -Wcast-qual -Wconversion -Wdouble-promotion -Wfloat-equal -Wswitch-default -Wswitch-enum -g
CFLAGS  := -std=c11 -O3 $(CERROR)

SRC_DIR   := src
INC_DIR   := lib
OUT_DIR   := build

SRC_FILES=$(wildcard $(SRC_DIR)/*.c)

$(PROJECT): $(SRC_FILES)
	mkdir -p build
	$(CC) $(CFLAGS) -I$(INC_DIR)/ -o $(OUT_DIR)/$(PROJECT) $(SRC_FILES)
	make run

.PHONY: run clean

run:
	./$(OUT_DIR)/$(PROJECT)

clean:
	rm $(OUT_DIR)/*
