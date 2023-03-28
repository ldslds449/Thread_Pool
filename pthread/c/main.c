#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "thread_pool.h"

#define NUM_OF_THREAD 4
#define NUM_OF_TASK 20
#define SLEEP_SECOND 3

// task args
typedef struct
{
  Thread_Pool *pool;
  int thread_id;
  int task_id;
} Task_Args;

// task return values
typedef struct
{
  int task_id;
  time_t finish_time;
} Task_Return_Data;

// task function
void *task(void *args)
{
  Task_Args *data = (Task_Args *)args;

  // sleep for a while
  printf("Task %d in Thread %d\n", data->task_id, data->thread_id);
  fflush(stdout);
  sleep(SLEEP_SECOND);

  // prepare return values
  Task_Return_Data *ret_data = (Task_Return_Data *)malloc(sizeof(Task_Return_Data));
  ret_data->task_id = data->task_id;
  ret_data->finish_time = time(NULL);

  Thread_Pool_Add(data->pool, data->thread_id);
  free(args);
  pthread_exit((void *)ret_data);
}

int main()
{
  Thread_Pool pool;
  Thread_Pool_Init(&pool, NUM_OF_THREAD);

  Task_Return_Data *data[NUM_OF_TASK];
  void *ret;

  // create tasks
  for (int i = 0; i < NUM_OF_TASK; ++i)
  {
    // get available thread id
    int id = Thread_Pool_Get(&pool);
    // check the return value
    pthread_join(pool.threads[id], &ret);
    if (ret != NULL)
    {
      Task_Return_Data *ret_data = ((Task_Return_Data *)ret);
      data[ret_data->task_id - 1] = ret_data;
    }
    // prepare the parameters
    Task_Args *args = (Task_Args *)malloc(sizeof(Task_Args));
    args->pool = &pool;
    args->thread_id = id;
    args->task_id = i + 1;
    // create the thread
    pthread_create(&(pool.threads[id]), NULL, task, args);
  }

  // wait for finishing all tasks
  for (int i = 0; i < pool.size; ++i)
  {
    pthread_join(pool.threads[i], &ret);
    if (ret != NULL)
    {
      Task_Return_Data *ret_data = ((Task_Return_Data *)ret);
      data[ret_data->task_id - 1] = ret_data;
    }
  }

  // deal with return values
  for (int i = 0; i < NUM_OF_TASK; ++i)
  {
    struct tm *stamp = localtime(&(data[i]->finish_time));
    printf("Task %d Finish At %04d-%02d-%02d %02d:%02d:%02d\n",
           data[i]->task_id,
           stamp->tm_year + 1900, stamp->tm_mon + 1, stamp->tm_mday,
           stamp->tm_hour, stamp->tm_min, stamp->tm_sec);
    fflush(stdout);
  }

  // free
  for (int i = 0; i < pool.size; ++i)
  {
    free(data[i]);
  }
  Thread_Pool_Destroy(&pool);

  return 0;
}