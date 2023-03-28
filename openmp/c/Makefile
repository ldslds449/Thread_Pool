GCC := gcc -Wall -g -O3
OPENMP := -fopenmp

SRC := main.c
EXEC := exec.main

for:
	$(GCC) $(SRC) -o $(EXEC) $(OPENMP) -DFOR_PARALLEL=1

task:
	$(GCC) $(SRC) -o $(EXEC) $(OPENMP) -DTASK_PARALLEL=1