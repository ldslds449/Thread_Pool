GCC := gcc -Wall -g -O3
PTHREAD := -lpthread

SRC := main.c queue.c thread_pool.c
EXEC := exec.main

all:
	$(GCC) $(SRC) -o $(EXEC) $(PTHREAD)