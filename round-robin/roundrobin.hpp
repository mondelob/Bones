#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

template <class T>
class RoundRobin {
    int N;                                  /* The number of elements */
    T * * set1;                             /* First set of the algorithm */
    T * * set2;                             /* Second set of the algorithm */
    void Shuffle();                         /* Mixes the sets */
    void Advance();                         /* Advances one round */
  public:
    RoundRobin(int N, ...);                 /* Constructor */
    RoundRobin(int N, T * * set);           /* Constructor */
    ~RoundRobin();                          /* Destructor */
    struct round {
      int rr_N;                             /* The number of rounds */
      T * * * rr_rounds;                    /* The defined rounds */
    };
    struct round * Round();                 /* Returns the actual round and advances the round */
};

template <class T>
RoundRobin<T>::RoundRobin(int N, ...) {

  va_list valist;

  va_start(valist, N);

  this->N = N;

  this->set1 = (T * *)malloc(sizeof(T) * N / 2);
  this->set2 = (T * *)malloc(sizeof(T) * N / 2);
  for (int i = 0; i < N / 2; i++) {
    this->set1[i] = (T *)malloc(sizeof(T));
    this->set1[i] = va_arg(valist, T *);
    this->set2[i] = (T *)malloc(sizeof(T));
    this->set2[i] = va_arg(valist, T *);
  }

  if (N % 2 != 0) {
    this->set1 = (T * *)realloc(this->set1, sizeof(T) * N / 2 + 1);
    this->set2 = (T * *)realloc(this->set2, sizeof(T) * N / 2 + 1);
    this->set1[N / 2] = (T *)malloc(sizeof(T));
    this->set1[N / 2] = va_arg(valist, T *);
    this->set2[N / 2] = NULL;
    this->N++;
  }

  va_end(valist);

  Shuffle();

}

template <class T>
RoundRobin<T>::RoundRobin(int N, T ** set) {

  this->N = N;

  this->set1 = (T * *)malloc(sizeof(T) * N / 2);
  this->set2 = (T * *)malloc(sizeof(T) * N / 2);
  for (int i = 0; i < N / 2; i++) {
    this->set1[i] = (T *)malloc(sizeof(T));
    this->set1[i] = set[i];
    this->set2[i] = (T *)malloc(sizeof(T));
    this->set2[i] = set[N - 1 - i];
  }

  if (N % 2 != 0) {
    this->set1 = (T * *)realloc(this->set1, sizeof(T) * N / 2 + 1);
    this->set2 = (T * *)realloc(this->set2, sizeof(T) * N / 2 + 1);
    this->set1[N / 2] = (T *)malloc(sizeof(T));
    this->set1[N / 2] = set[N / 2];
    this->set2[N / 2] = NULL;
    this->N++;
  }

  Shuffle();

}

template <class T>
void
RoundRobin<T>::Shuffle() {

  int j;
  T * * set, * old;

  srand (time(NULL));

  for (int i = 0; i < this->N / 2; i++) {
    old = this->set1[i];
    j = rand() % this->N;
    if (j < this->N / 2) {
      set = this->set1;
    }
    else {
      set = this->set2;
      j -= this->N / 2;
    }
    this->set1[i] = set[j];
    set[j] = old;
  }

  for (int i = 0; i < this->N / 2; i++) {
    old = this->set2[i];
    j = rand() % this->N;
    if (j < this->N / 2) {
      set = this->set1;
    }
    else {
      set = this->set2;
      j -= this->N / 2;
    }
    this->set2[i] = set[j];
    set[j] = old;
  }

}
/* Mixes the sets */

template <class T>
void
RoundRobin<T>::Advance() {
  T * actual, * old;
  actual = NULL;
  for (int i = 1; i < this->N / 2; i++) {
    old = this->set1[i];
    this->set1[i] = actual;
    actual = old;
  }
  for (int i = this->N / 2 - 1; i > 0; i--) {
    old = this->set2[i];
    this->set2[i] = actual;
    actual = old;
  }
  old = this->set2[0];
  this->set2[0] = actual;
  this->set1[1] = old;
}
/* Advances one round */

template <class T>
typename RoundRobin<T>::round *
RoundRobin<T>::Round() {
  struct round * r;
  r = (struct round *)malloc(sizeof(struct round));
  r->rr_N = this->N / 2;
  r->rr_rounds = (T * * *)malloc(sizeof(T) * N / 2);
  for (int i = 0; i < this->N / 2; i++) {
    r->rr_rounds[i] = (T * *)malloc(sizeof(T) * 2);
    r->rr_rounds[i][0] = this->set1[i];
    r->rr_rounds[i][1] = this->set2[i];
  }
  Advance();
  return r;
}

template <class T>
RoundRobin<T>::~RoundRobin() {
  free(this->set1);
  free(this->set2);
}
