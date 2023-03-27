#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <pthread.h>
#include "queue.h"

typedef struct{
  Queue q;
  pthread_t *threads;
  pthread_mutex_t q_mtx;
  pthread_cond_t q_cond;
  unsigned size;
} Thread_Pool;

void Thread_Pool_Init(Thread_Pool *pool, unsigned num_of_thread);
void Thread_Pool_Destroy(Thread_Pool *pool);
int Thread_Pool_Get(Thread_Pool *pool);
void Thread_Pool_Add(Thread_Pool *pool, int thread_id);
#endif