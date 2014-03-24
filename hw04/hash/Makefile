CFLAGS= -Wall -Wextra -ggdb


all: hash.c test.c unittest.c
	rm -rf hash
	gcc $(CFLAGS) -o hash test.c
	gcc $(CFLAGS) -o test unittest.c

test: hash.c unittest.c
	rm -rf hash
	gcc $(CFLAGS) -o test unittest.c 