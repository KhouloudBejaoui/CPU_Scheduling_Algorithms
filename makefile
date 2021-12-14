#les variables
SRC_DIR := politiques/src
BUILD_DIR := politiques/build

#fichier sources .c, wilcard est equivalent à *.c càd tous les fichiers.c
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

#variable flag
CFLAGS := -Wall -g

#compilateur object 
CC := gcc

# % compiler tous les fichiers .c en des fichiers executables
all: $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%) main
#attribution des droits (read, write et execute pour Owner / read et execute pour group et other)
	chmod 755 $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%) main 
	

main: main.c 
	$(CC) $(CFLAGS) main.c  -o main

#creation d'un dossier contenant les fichiers executables
$(BUILD_DIR)/%: $(SRC_DIR)/%.c 
	@mkdir -p $(@D)
	$(CC)  $(CFLAGS) -o $@ $^

#effacer le dossier build 
clean:
	rm -rf politiques/build
	rm -f main
