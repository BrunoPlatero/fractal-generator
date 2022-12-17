# Directories
SRC := src
INCLUDE := include
BIN := bin

# Compile Vars
CC := clang
CFLAGS := -I$(INCLUDE) -Wall -Wextra -Werror -fopenmp
LDFLAGS := -lomp -L/lib/llvm-14/lib
TARGET := $(BIN)/fractal

all: clean $(TARGET)

$(TARGET): bmp.o main.o fractal.o
	$(CC) $(LDFLAGS) $^ -o $@

bmp.o:
	$(CC) $(CFLAGS) -c $(SRC)/bmp.c -o $@

main.o:
	$(CC) $(CFLAGS) -c $(SRC)/main.c -o $@

fractal.o:
	$(CC) $(CFLAGS) -c $(SRC)/fractal.c -o $@

clean:
	rm -f $(TARGET)
	rm -f bmp.o main.o fractal.o $(TARGET)

run: all
	time ./$(TARGET)

tidy: clean
	mv *.bmp pics/

