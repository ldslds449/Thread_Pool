# Thread Pool

Implement thread pool in C and C++.

## pthread

Use `pthread` to implement thread pool in C.

- `main.c`: main file.
- `queue.h`, `queue.c`: Queue implement in C.
- `thread_pool.h`, `thread_pool.c`: Thread Pool implement in C.

Requirement:
- make (Optional)
- gcc

### Compile
```bash
cd ./pthread/c
make
```
or
```bash
gcc -Wall -g -O3 main.c queue.c thread_pool.c -o exec.main -lpthread
```
Note: `-lpthread` is needed.

### Run

```bash
./exec.main
```

## std::thread

Use `std::thread` to implement thread pool in C++.

- `main.cpp`: main file.
- `thread_pool.h`, `thread_pool.cpp`: Thread Pool implement in C++.

Requirement:
- make (Optional)
- g++

### Compile
```bash
cd ./std_thread/cpp
make
```
or
```bash
g++ -Wall -g -O3 -std=c++11 main.cpp thread_pool.cpp -o exec.main -lpthread
```
Note: `-lpthread` and `-std=c++11` is needed.

### Run

```bash
./exec.main
```

## OpenMP

Use `OpenMP` to implement thread pool in C. If the tasks is different only in parameters, we can use parallel for to do the tasks in parallel. Otherwise, we can use task to do different task in parallel. 

- `main.c`: main file.

Requirement:
- make (Optional)
- gcc
- OpenMP supported

### Compile
```bash
cd ./openmp/c
make for
# or
make task
```
or
```bash
gcc -Wall -g -O3 main.c -o exec.main -fopenmp -DFOR_PARALLEL=1
# or
gcc -Wall -g -O3 main.c -o exec.main -fopenmp -DTASK_PARALLEL=1
```
Note: `-fopenmp` is needed.

### Run

```bash
./exec.main
```

## Reference

* [how-to-utilize-a-thread-pool-with-pthreads](https://stackoverflow.com/questions/6954489/how-to-utilize-a-thread-pool-with-pthreads)  
* [how-to-return-a-value-from-pthread-threads-in-c](https://stackoverflow.com/questions/2251452/how-to-return-a-value-from-pthread-threads-in-c)
* [C++11 Thread 的 condition variable](https://kheresy.wordpress.com/2014/01/09/c11-condition-variable/)
* [C++11 程式的平行化：async 與 future](https://kheresy.wordpress.com/2016/03/14/async-and-future-in-c11/)
* [std::condition_variable 用法與範例](https://shengyu7697.github.io/std-condition_variable/)
* [C++: Simple return value from std::thread?](https://stackoverflow.com/questions/7686939/c-simple-return-value-from-stdthread)
* [C++ std::thread 建立多執行緒用法與範例](https://shengyu7697.github.io/std-thread/)
* [How does the omp ordered clause work?](https://stackoverflow.com/questions/13224155/how-does-the-omp-ordered-clause-work)
* [OpenMP3.0的新特性Task指令基础](https://blog.csdn.net/gengshenghong/article/details/7004594)
