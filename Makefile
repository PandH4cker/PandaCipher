CC = gcc
CC_FLAGS = -Wall -lm
exe = pandaCipher

all: compile

run: compile
	./$(exe)

compile:
	$(CC) $(CC_FLAGS) src/*.c -o $(exe)

clean:
	rm -rf $(exe)