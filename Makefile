CC = gcc
CC_FLAGS = -Wall -O3
exe = pandaCipher

all: run

run: compile
	./$(exe)

compile:
	$(CC) $(CC_FLAGS) src/*.c -o $(exe)

clean:
	rm -rf $(exe)