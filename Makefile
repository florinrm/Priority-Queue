all: build

build:
	gcc -Wall -g source.c -o source

clean:
	rm source