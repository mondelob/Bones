#include <stdexcept>
#include <string.h>

class PriorityQueue {
    int size;                                   /* Size of the queue */
    int N;                                      /* Num of elements */
    int * heap;                                 /* The array of elements */
    void Resize(int size);                      /* Resizes the array size */
    void Exchange(int i, int j);                /* Exchange the positions of two values */
    int Max(int i, int j, int k);               /* Returns the max of three rows */
    void Swap(int i);                           /* Swaps with higher positions */
    void Swim(int i);                           /* Swims with lower positions */
  public:
    PriorityQueue();                            /* Constructor */
    ~PriorityQueue();                           /* Destructor */
    void Insert(int element);                   /* Inserts an element */
    int GetMax();                               /* Returns the max item */
    int RemoveMax();                            /* Returns and removes teh max item */
    void Show();                                /* TMP erase !!! */
};

PriorityQueue::PriorityQueue() {
  this->N = 0;
  this->size = 1;
  this->heap = (int *)malloc(sizeof(int));
  this->heap[0] = -1;
}
/* Constructor */

PriorityQueue::~PriorityQueue() {
  free(this->heap);
}
/* Destructor */

void
PriorityQueue::Resize(int size) {
  int old = this->size;
  this->size = size;
  this->heap = (int *)realloc(this->heap, sizeof(int) * size);
  for (int i = old; i < size; i++)
    this->heap[i] = -1;
}
/* Resizes the array size */

void
PriorityQueue::Exchange(int i, int j) {
  int element = this->heap[i];
  this->heap[i] = this->heap[j];
  this->heap[j] = element;
}
/* Exchange the positions of two values */

int
PriorityQueue::Max(int i, int j, int k) {
  int maxval = i;
  if (this->heap[i] < this->heap[j])
    maxval = j;
  if (this->heap[maxval] < this->heap[k])
    maxval = k;
  return maxval;
}
/* Returns the max of three rows */

void
PriorityQueue::Swap(int i) {
  while (this->heap[i] > this->heap[i/2] && i > 1) {
    Exchange(i, i/2);
    i = i / 2;
  }
}
/* Swaps with higher positions */

void
PriorityQueue::Swim(int i) {
  int maxval;
  while (i < this->N && i * 2 + 1 < this->size - 1) {
    maxval = Max(i, i * 2, i * 2 + 1);
    if (maxval == i * 2) {
      Exchange(i, i * 2);
      i = i * 2;
    }
    else if (maxval == i * 2 + 1) {
      Exchange(i, i * 2 + 1);
      i = i * 2 + 1;
    }
    else {
      i = this->N;
    }
  }
}
/* Swims with lower positions */

void
PriorityQueue::Insert(int element) {
  if (this->N == this->size - 1)
    Resize(this->size * 2);
  this->N++;
  this->heap[this->N] = element;
  Swap(this->N);
}
/* Inserts an element */

int
PriorityQueue::GetMax() {
  if (this->size <= 1)
    throw std::underflow_error("no elements on heap");
  return this->heap[1];
}
/* Returns the max item */

int
PriorityQueue::RemoveMax() {
  if (this->size <= 1)
    throw std::underflow_error("no elements on heap");
  int element = heap[1];
  this->heap[1] = this->heap[this->N];
  this->heap[this->N] = -1;
  this->N--;
  Swim(1);
  if (this->N <= this->size / 4)
    Resize(this->size / 2);
  return element;
}
/* Returns and removes teh max item */

void
PriorityQueue::Show() {
  std::cout << "{";
  for (int i = 0; i < this->size; i++)
    std::cout << this->heap[i] << ", ";
  std::cout << "\b\b}\n";
}
