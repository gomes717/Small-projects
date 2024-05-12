CC = gcc
CFLAGS = -Wall
LDFLAGS =
SDIR = ./src
SRC = main.c sudoku.c printer.c entropy.c solver.c
LDIR = ./include
LIB = utils.h defs.h structs.h
TARGET = sudokuSolver
ODIR = ./obj
OBJ = $(SRC:.c=.o)

all: $(TARGET)
	rm -f $(OBJ)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(CFLAGS)

%.o:$(SDIR)/%.c 
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(OBJ) $(TARGET) *~
