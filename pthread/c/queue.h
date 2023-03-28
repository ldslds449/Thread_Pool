#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct
{
  int *arr;
  unsigned max_size, size, start;
} Queue;

void Queue_Init(Queue *q, unsigned max_size);
void Queue_Destroy(Queue *q);
int Queue_Empty(Queue *q);
int Queue_Full(Queue *q);
int Queue_Push(Queue *q, int element);
int Queue_Front(Queue *q, int *element);
void Queue_Pop(Queue *q);

#endif