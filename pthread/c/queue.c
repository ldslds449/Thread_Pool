#include <stdlib.h>
#include "queue.h"

void Queue_Init(Queue *q, unsigned max_size)
{
  q->max_size = max_size;
  q->arr = (int *)malloc(sizeof(int) * max_size);
  q->start = q->size = 0;
}

void Queue_Destroy(Queue *q)
{
  free(q->arr);
}

int Queue_Empty(Queue *q)
{
  return q->size == 0;
}

int Queue_Full(Queue *q)
{
  return q->size == q->max_size;
}

int Queue_Push(Queue *q, int element)
{
  if (Queue_Full(q))
    return 1;
  unsigned add_idx = (q->start + q->size < q->max_size ? (q->start + q->size) : (q->start + q->size - q->max_size));
  q->arr[add_idx] = element;
  q->size += 1;
  return 0;
}

int Queue_Front(Queue *q, int *element)
{
  if (Queue_Empty(q))
    return 1;
  *element = q->arr[q->start];
  return 0;
}

void Queue_Pop(Queue *q)
{
  if (Queue_Empty(q))
    return;
  q->size -= 1;
  q->start += 1;
  if (q->start == q->max_size)
    q->start = 0;
}