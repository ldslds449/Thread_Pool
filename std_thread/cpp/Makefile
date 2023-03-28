G_PLUS_PLUS := g++ -Wall -g -O3 -std=c++11
PTHREAD := -lpthread

SRC := main.cpp thread_pool.cpp
EXEC := exec.main

all:
	$(G_PLUS_PLUS) $(SRC) -o $(EXEC) $(PTHREAD)