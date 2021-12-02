
SRC_DIR := politiques/src
BUILD_DIR := politiques/build
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
CFLAGS := -Wall -g

all: $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%) main
main: main.c
	gcc $(CFLAGS) main.c -o main

$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	gcc $(CFLAGS) $< -o $@

clean:
	rm -rf politiques/build
	rm -f main
