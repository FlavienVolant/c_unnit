CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
LDFLAGS = -lm
OUT = out

exemples: $(OUT)/example_01

$(OUT)/example_01: examples/example_01.c src/c_unnit.c | $(OUT)
	$(CC) $(CFLAGS) -o $@ examples/example_01.c src/c_unnit.c $(LDFLAGS)

$(OUT):
	mkdir -p $(OUT)

clean:
	rm -rf $(OUT)
