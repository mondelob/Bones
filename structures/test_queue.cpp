#include <iostream>
#include <string>
#include "src/queue.h"

using namespace std;

int
main() {

  string userinput;
  /* The user input message */

  string retval;
  /* The result of the dequeue */

  Queue<string> q;
  /* The Queue */

  while (true) {
    getline(cin, userinput);
    if (userinput.compare("-") <= 0)
    {
      retval = q.Dequeue();
      cout << "Dequeued value: '" << retval << "'\n";
    }
    else
    {
      q.Enqueue(userinput);
      cout << "Enqueued value: '" << userinput << "'\n";
    }
  }

  return 0;
}
