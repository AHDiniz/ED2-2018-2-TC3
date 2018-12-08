# ED2-2018-2-TC3: Password Cracking problem
#  
# Authors: Alan Herculano Diniz & Rafael Belmock Pedruzzi
#  
# Project's build file

SRC = src

BIN = bin

INC = include

CC = gcc

FLAGS = -Wall -g -O3 -w

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

BSRC = $(wildcard $(SRC)/brute/*.c)

DSRC = $(wildcard $(SRC)/decrypt/*.c)

INCLUDES = $(wildcard $(INC)/*.h)

BRUTE = $(BIN)/$(BNAME)

DECRYPT = $(BIN)/$(DNAME)

PWD = h554tkdzti

RAND = in/rand10.txt

compile: $(BRUTE) $(DECRYPT)

symbolTable: $(BIN)/st_test

bin/encrypt: notUsing/encrypt.c src/key.c include/key.h
	$(CC) -o $@ $^ $(FLAGS)

$(BIN)/st_test: $(SRC)/st_tree.c $(SRC)/st_tester.c $(SRC)/key.c
	$(CC) -o $@ $^ $(FLAGS)

$(BRUTE): $(SOURCES) $(INCLUDES) $(BSRC)
	$(CC) -o $@ $^ $(FLAGS)

$(DECRYPT): $(SOURCES) $(INCLUDES) $(DSRC)
	$(CC) -o $@ $^ $(FLAGS)

clean:
	rm $(BIN)/*.o

runDec:
	time ./$(DECRYPT) $(PWD) < $(RAND)
