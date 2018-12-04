# ED2-2018-2-TC3: Password Cracking problem
#  
# Authors: Alan Herculano Diniz & Rafael Belmock Pedruzzi
#  
# Project's build file

SRC = src

BIN = bin

INC = include

CC = gcc

FLAGS = -Wall -g

ifeq ($(OS), Windows_NT)
	BNAME = brute.exe
else
	BNAME = brute
endif

ifeq ($(OS), Windows_NT)
	DNAME = decrypt.exe
else
	DNAME = decrypt
endif

SOURCES = $(wildcard $(SRC)/*.c)

INCLUDES = $(wildcard $(INC)/*.h)

BRUTE = $(BIN)/$(BNAME)

DECRYPT = $(BIN)/$(DNAME)

compile: $(BRUTE) $(DECRYPT)

symbolTable: $(BIN)/st_test

$(BIN)/st_test: $(SRC)/st_tree.c $(SRC)/st_tester.c $(SRC)/key.c
	$(CC) -o $@ $^ $(FLAGS)

$(BRUTE): $(SOURCES) $(INCLUDES)
	$(CC) -o $@ $^ $(FLAGS)

$(DECRYPT): $(SOURCES) $(INCLUDES)
	$(CC) -o $@ $^ $(FLAGS)

clean:
	rm $(BIN)/*.o
