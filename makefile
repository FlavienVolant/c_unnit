example: examples/example.c src/c_unnit.c
	gcc -Iinclude -o example examples/example.c src/c_unnit.c -lm

clean:
	rm -f example
