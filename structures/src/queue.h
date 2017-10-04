using namespace std;

template <class T>
class Queue {
  private:
    class Node {
      public:
        T Item;
        /* The value of the Node */
        Node * Next;
        /* The next node */
    };
    /* The structure of every node of the linked list */
    int N;
    /* The actual count of elements on the queue */
    Node * First;
    /* The first node */
    Node * Last;
    /* The lasts node */
  public:
    Queue();
    /* The queue constructor */
    bool IsEmpty();
    /* Status of the Queue */
    int Size();
    /* Size of the Queue */
    void Enqueue(T item);
    /* Add item to Queue */
    T Dequeue();
    /* Remove item on Queue */
    T Peek();
    /* Returns item on Stack */
};
/* Implements a queue based on a linked list */

template <class T>
Queue<T>::Queue() {
  this->N = 0;
  this->First = NULL;
  this->Last = NULL;
}
/* Constructor of the queue */

template <class T> bool
Queue<T>::IsEmpty() {
  return this->First == NULL;
}
/* The actual status of the queue */

template <class T> int
Queue<T>::Size() {
  return this->N;
}
/* The actual size of the queue */

template <class T> void
Queue<T>::Enqueue(T item) {
  Node * oldlast = this->Last;
  this->Last = new Node();
  this->Last->Item = item;
  this->Last->Next = NULL;
  if (this->IsEmpty())
    this->First = this->Last;
  else
    oldlast->Next = this->Last;
  this->N++;
}
/* Adds an item to the Queue on the last place */

template <class T> T
Queue<T>::Dequeue() {
  if (this->IsEmpty())
    throw underflow_error("Stack has no items");
  T item = this->First->Item;
  this->First = this->First->Next;
  if (this->IsEmpty())
    this->Last = NULL;
  this->N--;
  return item;
}
/* Returns and removes the lest item added on the Queue */

template <class T> T
Queue<T>::Peek() {
  if (this->IsEmpty())
    throw underflow_error("Stack has no items");
  return this->First->Item;
}
/* Returns (but no removes) the least item added on the Queue */
