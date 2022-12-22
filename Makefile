# Directories
SRC := src
INCLUDE := include
BIN := bin
DIST := dist

# Compile Vars
CC := gcc
CFLAGS := -I$(INCLUDE) -Wall -Wextra -Werror -O3
LDFLAGS := -fopenmp -flto -lSDL2
TARGET := $(BIN)/fractal

all: clean setup $(TARGET)

setup:
	mkdir -p $(BIN) $(DIST)

$(TARGET): $(DIST)/bmp.o $(DIST)/main.o $(DIST)/fractal.o 
	time $(CC) $(LDFLAGS) $^ -o $@ -lSDL2

$(DIST)/bmp.o:
	$(CC) $(CFLAGS) -c $(SRC)/bmp.c -o $@

$(DIST)/main.o:
	$(CC) $(CFLAGS) -c $(SRC)/main.c -o $@

$(DIST)/fractal.o:
	$(CC) $(CFLAGS) -fopenmp -c $(SRC)/fractal.c -o $@

clean:
	rm -rf $(BIN) $(DIST)

run: all
	./$(TARGET)

tidy: clean
	mkdir -p pics/
	mv *.bmp pics/

# This makefile target requires bear. Do: 'sudo apt update' and 'sudo apt -y install bear'
clangd:
	bear --output compile_commands.json -- make
