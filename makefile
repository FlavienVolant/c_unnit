CC = gcc
CFLAGS = -Iinclude -Wextra
LDFLAGS = -lm
OUT = out
C_UNNIT = src/c_unnit.c include/c_unnit.h
C_UNNIT_PPT = src/c_unnit.c include/c_unnit.h src/c_unnit_ppt.c include/c_unnit_ppt.h

exemples: $(OUT)/example_01 $(OUT)/example_02 $(OUT)/example_ppt_01

$(OUT)/example_01: examples/example_01.c $(C_UNNIT) | $(OUT)
	$(CC) $(CFLAGS) -o $@ examples/example_01.c src/c_unnit.c $(LDFLAGS)

$(OUT)/example_02: examples/example_02.c $(C_UNNIT) | $(OUT)
	$(CC) $(CFLAGS) -o $@ examples/example_02.c src/c_unnit.c $(LDFLAGS)

$(OUT)/example_ppt_01: examples/example_ppt_01.c $(C_UNNIT_PPT) | $(OUT)
	$(CC) $(CFLAGS) -o $@ examples/example_ppt_01.c src/c_unnit.c src/c_unnit_ppt.c $(LDFLAGS)

$(OUT):
	mkdir -p $(OUT)

clean:
	rm -rf $(OUT)
