CC=gcc
CFLAGS=-g -std=c99 -Wall -lncurses -pthread
TMP_DIR=tmp

all: $(TMP_DIR) main

$(TMP_DIR):
	mkdir $(TMP_DIR)

$(TMP_DIR)/%.o: ./%.c
	$(CC) $(CFLAGS) -c $^
	mv *.o $(TMP_DIR)

main: $(TMP_DIR)/*.o
	gcc $^ -o $@ $(CFLAGS)
	./$@

game:
	./main

clean:
	rm -r $(TMP_DIR)
