CC = gcc
CFLAGS = -g -O0 -std=c99
CPPFLAGS = 
LDFLAGS =
LDLIBS =

SRC := ./src
TESTS := ./tests
BUILD := ./build
LIBS := ./libs
OUT := ./out


all: tests

tests-quiet: CPPFLAGS += -DQUIET
tests-quiet: tests

tests-debug: CPPFLAGS += -DDEBUG -g
tests-debug: tests

tests: $(BUILD)/main.o $(BUILD)/polynom.o
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(BUILD)/main.o $(BUILD)/polynom.o -o $(TESTS)/main

$(BUILD)/main.o: $(TESTS)/main.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(TESTS)/main.c -o $(BUILD)/main.o

$(BUILD)/polynom.o: $(SRC)/polynom.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(SRC)/polynom.c -o $(BUILD)/polynom.o

clean:
	rm -f ./tests/main; rm -f ./build/*









