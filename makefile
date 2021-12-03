#desVariables dans makefile
SRC_DIR := politiques/src
BUILD_DIR := politiques/build

#fichier sources .c willcard equivo a *.c en unix tous les fichier
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

OBJS = $(patsubst %,$(BUILD_DIR)/%,$(SRC_FILES))
#variable flag
CFLAGS := -Wall -g 
#compilateur object 
CC := gcc

#%compiler tous me fichier .c en des fichiers executables
all: $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%) main
main: main.c 
	$(CC) $(CFLAGS) main.c  -o main

$(BUILD_DIR)/%: $(SRC_DIR)/%.c 
	@mkdir -p $(@D)
	$(CC) -nostartfiles $(CFLAGS) -o $@ $^

#nettoyer mes fichier objets
clean:
	rm -rf politiques/build
	rm -f main