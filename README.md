# Thread Pool

Implement thread pool in C and C++.

## C (pthread)

Use `pthread` to implement thread pool in C.

- `main.c`: main file.
- `queue.h`, `queue.c`: Queue implement in C.
- `thread_pool.h`, `thread_pool.c`: Thread Pool implement in C.

Requirement:
- make (Optional)
- gcc

### Compile
```bash
cd ./c
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

## C++ (std::thread)

TBA

## Reference

* [how-to-utilize-a-thread-pool-with-pthreads](https://stackoverflow.com/questions/6954489/how-to-utilize-a-thread-pool-with-pthreads)  
* [how-to-return-a-value-from-pthread-threads-in-c](https://stackoverflow.com/questions/2251452/how-to-return-a-value-from-pthread-threads-in-c)