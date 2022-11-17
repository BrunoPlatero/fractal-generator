# Directories
SRC := src
INCLUDE := include

# Compile Vars
CC := clang
CFLAGS := -I$(INCLUDE) -Wall -Wextra -Werror
LDFLAGS :=
TARGET := hello

all: clean $(TARGET)

$(TARGET): bmp.o main.o
	$(CC) $(LDFLAGS) $^ -o $@

bmp.o:
	$(CC) $(CFLAGS) -c $(SRC)/bmp.c -o $@

main.o:
	$(CC) $(CFLAGS) -c $(SRC)/main.c -o $@

clean:
	rm -f bmp.o main.o $(TARGET)

run: all
	./$(TARGET)