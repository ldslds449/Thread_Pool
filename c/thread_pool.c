#include <stdlib.h>
#include <pthread.h>
#include "thread_pool.h"

void Thread_Pool_Init(Thread_Pool *pool, unsigned num_of_thread){
  pool->size = num_of_thread;
  Queue_Init(&(pool->q), num_of_thread);
  for(int i = 0; i < num_of_thread; ++i) Queue_Push(&(pool->q), i);
  pool->threads = (pthread_t*)malloc(sizeof(pthread_t) * num_of_thread);
  pthread_mutex_init(&(pool->q_mtx), NULL);
  pthread_cond_init(&(pool->q_cond), NULL);
}

void Thread_Pool_Destroy(Thread_Pool *pool){
  Queue_Destroy(&(pool->q));
  free(pool->threads);
  pthread_mutex_destroy(&(pool->q_mtx));
  pthread_cond_destroy(&(pool->q_cond));
}

int Thread_Pool_Get(Thread_Pool *pool){
  pthread_mutex_lock(&(pool->q_mtx));
  while(Queue_Empty(&(pool->q))){
    pthread_cond_wait(&(pool->q_cond), &(pool->q_mtx));
  }
  int thread_id;
  Queue_Front(&(pool->q), &thread_id);
  Queue_Pop(&(pool->q));
  pthread_mutex_unlock(&(pool->q_mtx));
  return thread_id;
}

void Thread_Pool_Add(Thread_Pool *pool, int thread_id){
  pthread_mutex_lock(&(pool->q_mtx));
  Queue_Push(&(pool->q), thread_id);
  pthread_mutex_unlock(&(pool->q_mtx));
  pthread_cond_signal(&(pool->q_cond));
}