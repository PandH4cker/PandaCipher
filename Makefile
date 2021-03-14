CC = gcc
CC_FLAGS = -Wall -lm
exe = pandaCipher

all: run

run: compile
	./$(exe) --help

compile:
	$(CC) $(CC_FLAGS) src/*.c -o $(exe)

clean:
	rm -rf $(exe)