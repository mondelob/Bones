#include <iostream>
#include <ctime>
#include "src/priorityqueue.hpp"
#include "array.h" /* int test []*/

#define MAX_TEST 999999

using namespace std;

int
main(int argc, char * argv[]) {

  clock_t begin, end;
  double elapsed;

  PriorityQueue q;

  begin = clock();
  for (int i = 0; i <= MAX_TEST; i++)
    q.Insert(test[i]);
  end = clock();
  elapsed = double(end - begin) / CLOCKS_PER_SEC;
  cout << "Elapsed time loading : " << elapsed << "s\n";

  begin = clock();
  for (int i = 0; i <= MAX_TEST; i++)
    cerr << "out : " << q.RemoveMax() << "\n";
  end = clock();
  elapsed = double(end - begin) / CLOCKS_PER_SEC;
  cout << "Elapsed time showing : " << elapsed << "s\n";

  return 0;

}
