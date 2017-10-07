#include <iostream>
#include <string>
#include "src/stack.h"

using namespace std;

int
main() {

  string userinput;
  /* The user input message */

  string retval;
  /* The result of the pops */

  Stack<string> s;
  /* The Stack */

  while (true) {
    getline(cin, userinput);
    if (userinput.compare("-") <= 0)
    {
      retval = s.Pop();
      cout << "Popped value: '" << retval << "'\n";
    }
    else
    {
      s.Push(userinput);
      cout << "Push value: '" << userinput << "'\n";
    }
  }

  return 0;
}
