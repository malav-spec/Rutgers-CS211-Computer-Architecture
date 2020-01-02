all: second

first: second.c
	gcc -Wall -Werror -fsanitize=address -std=c11 second.c -o second

clean:
	rm -f second

