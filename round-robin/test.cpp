#include <iostream>
#include "roundrobin.hpp"

using namespace std;

struct Person {
  char * name;            /* Name of the person */
  struct Person * met;    /* Persons already met */
};

int
main() {
  struct RoundRobin<struct Person>::round * r;
  struct Person p1, p2, p3, p4, p5;
  p1.name = (char *)"Pere";
  p2.name = (char *)"Marta";
  p3.name = (char *)"Anna";
  p4.name = (char *)"Joan";
  p5.name = (char *)"Xavi";

  struct Person * persons[5] = {&p1, &p2, &p3, &p4, &p5};

  RoundRobin<struct Person> interface(5, persons);
  // RoundRobin<struct Person> interface(5, &p1, &p2, &p3, &p4, &p5);
  for (int i = 0; i < 5; i++) {
    cout << "\nRound: " << i + 1 << "\n";
    r = interface.Round();
    for (int i = 0; i < r->rr_N; i++) {
      if (r->rr_rounds[i][0] != NULL)
        cout << r->rr_rounds[i][0]->name;
      else
        cout << "-";
      cout << " VS ";
      if (r->rr_rounds[i][1] != NULL)
        cout << r->rr_rounds[i][1]->name;
      else
        cout << "-";
      cout << "\n";
    }
  }

  return 0;
}
