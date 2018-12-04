# ED2-2018-2-TC3: Password Cracking problem
#  
# Authors: Alan Herculano Diniz & Rafael Belmock Pedruzzi
#  
# Project's build file

SRC = src

BIN = bin

CC = gcc

FLAGS = -Wall -g

ifeq ($(OS), Windows_NT)
	TARGET = brute.exe
else
	TARGET = brute
endif

SOURCES = $(wildcard $(SRC)/*.c)

EXE = $(BIN)/$(TARGET)

compile: $(EXE)

$(BIN)/st_test: $(SRC)/st_tree.c $(SRC)/st_tester.c
	$(CC) -o $@ $^ $(FLAGS)

$(EXE): $(SOURCES)
	$(CC) -o $@ $^ $(FLAGS)

clean:
	rm $(BIN)/*.o
