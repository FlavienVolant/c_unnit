CC = gcc
CFLAGS = -Iinclude -Wextra
LDFLAGS = -lm
OUT = out
C_UNNIT = src/c_unnit.c include/c_unnit.h

exemples: $(OUT)/example_01 $(OUT)/example_02

$(OUT)/example_01: examples/example_01.c $(C_UNNIT) | $(OUT)
	$(CC) $(CFLAGS) -o $@ examples/example_01.c src/c_unnit.c $(LDFLAGS)

$(OUT)/example_02: examples/example_02.c $(C_UNNIT) | $(OUT)
	$(CC) $(CFLAGS) -o $@ examples/example_02.c src/c_unnit.c $(LDFLAGS)

$(OUT):
	mkdir -p $(OUT)

clean:
	rm -rf $(OUT)
