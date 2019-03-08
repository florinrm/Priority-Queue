CC = gcc
CFLAGS = -Wall -fPIC -g

LDFLAGS = -L.

build: tema1

tema1: source.c
	$(CC) $(CFLAGS) -o $@ $< -lcompare -lso $(LDFLAGS)
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
clean:
	rm -f *.o  tema1
