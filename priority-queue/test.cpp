#include <iostream>
#include "priorityqueue.hpp"

using namespace std;

int
main(int argc, char * argv[]) {

  PriorityQueue q;
  q.Insert(3);
  q.Insert(8);
  q.Insert(4);
  q.Insert(1);
  q.Insert(9);
  q.Insert(2);
  q.Show();
  cout << "RemoveMax(): " << q.RemoveMax() << "\n";
  cout << "RemoveMax(): " << q.RemoveMax() << "\n";
  cout << "RemoveMax(): " << q.RemoveMax() << "\n";
  cout << "RemoveMax(): " << q.RemoveMax() << "\n";
  cout << "RemoveMax(): " << q.RemoveMax() << "\n";
  cout << "RemoveMax(): " << q.RemoveMax() << "\n";
  cout << "RemoveMax(): " << q.RemoveMax() << "\n";
  q.Show();
  // cout << "RemoveMax(): " << q.RemoveMax() << "\n";

  return 0;

}
