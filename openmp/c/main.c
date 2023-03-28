#include <omp.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define NUM_OF_THREAD 4
#define NUM_OF_TASK 20
#define SLEEP_SECOND 3

// task function
time_t task(int task_id)
{
  // sleep for a while
  printf("Task %d in Thread %d\n", task_id, omp_get_thread_num());
  fflush(stdout);
  sleep(SLEEP_SECOND);

  // return values
  return time(NULL);
}

int main()
{
  time_t data[NUM_OF_TASK];

#ifdef FOR_PARALLEL
  printf("Use For Parallel\n");
  // parallel
  #pragma omp parallel for schedule(static, 1) shared(data) num_threads(NUM_OF_THREAD)
  for (int i = 0; i < NUM_OF_TASK; ++i)
  {
    // call tasks
    data[i] = task(i + 1);
  }
#endif

#ifdef TASK_PARALLEL
  printf("Use Task Parallel\n");
  // parallel
  #pragma omp parallel shared(data) num_threads(NUM_OF_THREAD)
  {
    #pragma omp single
    {
      for (int i = 0; i < NUM_OF_TASK; ++i)
      {
        // call tasks
        #pragma omp task
        data[i] = task(i + 1);
      }
    }
  }

#endif

  // deal with return values
  for (int i = 0; i < NUM_OF_TASK; ++i)
  {
    struct tm *stamp = localtime(data + i);
    printf("Task %d Finish At %04d-%02d-%02d %02d:%02d:%02d\n",
           i,
           stamp->tm_year + 1900, stamp->tm_mon + 1, stamp->tm_mday,
           stamp->tm_hour, stamp->tm_min, stamp->tm_sec);
    fflush(stdout);
  }

  return 0;
}