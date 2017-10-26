#include <stdlib.h>

struct priorityqueue {
  int size;     /* Size of the queue */
  int N;        /* Actual elements on the queue */
  int * heap;   /* Array containing all elements */
};
/* The priority queue structure */

void
init_queue(struct priorityqueue * q) {
  q->N = 0;
  q->size = 1;
  q->heap = malloc(sizeof(int));
  q->heap[0] = -1;
}
/* Initializes the queue */

void
free_queue(struct priorityqueue * q) {
  free(q->heap);
}
/* Frees the queue memory usage */

void
resize_queue(struct priorityqueue * q, int size) {
  int old = q->size;
  q->size = size;
  q->heap = realloc(q->heap, sizeof(int) * size);
  for (int i = old; i < size; i++)
    q->heap[i] = -1;
}
/* Resizes the array size */

void
exchange_queue(struct priorityqueue * q, int i, int j) {
  int element = q->heap[i];
  q->heap[i] = q->heap[j];
  q->heap[j] = element;
}
/* Exchanges the position of two elements */

int
max_queue(struct priorityqueue * q, int i, int j, int k) {
  int maxval = i;
  if (q->heap[maxval] < q->heap[j])
    maxval = j;
  if (q->heap[maxval] < q->heap[k])
    maxval = k;
  return maxval;
}
/* Returns the max of three elements */

void
swap_queue(struct priorityqueue * q, int i) {
  while (q->heap[i] > q->heap[i / 2] && i > 1) {
    exchange_queue(q, i, i / 2);
    i = i / 2;
  }
}
/* Swaps with higher positions */

void
swim_queue(struct priorityqueue * q, int i) {
  int maxval;
  while (i < q->N && i * 2 + 1 < q->size - 1) {
    maxval = max_queue(q, i, i * 2, i * 2 + 1);
    if (maxval == i * 2) {
      exchange_queue(q, i, i * 2);
      i = i * 2;
    }
    else if (maxval == i * 2 + 1) {
      exchange_queue(q, i, i * 2 + 1);
      i = i * 2 + 1;
    }
    else {
      i = q->N;
    }
  }
}
/* Swims with lower positions */

void
insert_queue(struct priorityqueue * q, int element) {
  if (q->N == q->size - 1)
    resize_queue(q, q->size * 2);
  q->N++;
  q->heap[q->N] = element;
  swap_queue(q, q->N);
}
/* Inserts an element */

int
root_queue(struct priorityqueue * q) {
  if (q->size <= 1) {
    perror("no elements on heap");
    return -1;
  }
  return q->heap[1];
}
/* Returns the max item */

int
remove_queue(struct priorityqueue * q) {
  if (q->size <= 1)
    perror("no elements on heap");
  int element = q->heap[1];
  q->heap[1] = q->heap[q->N];
  q->heap[q->N] = -1;
  q->N--;
  swim_queue(q, 1);
  if (q->N <= q->size / 4)
    resize_queue(q, q->size / 2);
  return element;
}
/* Returns and removes teh max item */

void
show_queue(struct priorityqueue * q) {
  printf("{");
  for (int i = 0; i < q->size; i++)
    printf("%d, ", q->heap[i]);
  printf("\b\b}\n");
}
