all: first

first: first.c 
	gcc -g -Wall -lm -Werror -fsanitize=address -std=c11 first.c -o first
clean:
	rm -f first
