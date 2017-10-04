using namespace std;

template <class T>
class Stack {
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
    /* The actual count of elements on the stack */
    Node * First;
    /* The first node */
  public:
    Stack();
    /* The stack constructor */
    bool IsEmpty();
    /* Status of the Stack */
    int Size();
    /* Size of the Stack */
    void Push(T item);
    /* Add item to Stack */
    T Pop();
    /* Remove item on Stack */
    T Peek();
    /* Returns item on Stack */
};
/* Implements a stack based on a linked list */

template <class T>
Stack<T>::Stack() {
  this->N = 0;
  this->First = NULL;
}
/* Constructor of the stack */

template <class T> bool
Stack<T>::IsEmpty() {
  return this->First == NULL;
}
/* The actual status of the stack */

template <class T> int
Stack<T>::Size() {
  return this->N;
}
/* The actual size of the stack */

template <class T> void
Stack<T>::Push(T item) {
  Node * oldFirst = this->First;
  this->First = new Node();
  this->First->Item = item;
  this->First->Next = oldFirst;
  this->N++;
}
/* Adds an item to the Stack on the first place */

template <class T> T
Stack<T>::Pop() {
  if (this->IsEmpty())
    throw underflow_error("Stack has no items");
  T item = this->First->Item;
  this->First = this->First->Next;
  this->N--;
  return item;
}
/* Returns and removes the last item added on the Stack */

template <class T> T
Stack<T>::Peek() {
  if (this->IsEmpty())
    throw underflow_error("Stack has no items");
  return this->First->Item;
}
/* Returns (but no removes) the last item added on the Stack */
