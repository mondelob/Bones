#include <stdio.h>
#include <time.h>
#include "src/priorityqueue.h"
#include "array.h" /* int test []*/

#define MAX_TEST 999999

int
main(int argc, char * argv[]) {

  clock_t begin, end;
  double elapsed;

  struct priorityqueue q;

  init_queue(&q);

  begin = clock();
  for (int i = 0; i <= MAX_TEST; i++)
    insert_queue(&q, test[i]);
  end = clock();
  elapsed = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Elapsed time loading : %fs\n", elapsed);

  begin = clock();
  for (int i = 0; i <= MAX_TEST; i++)
    fprintf(stderr, "out : %d\n", remove_queue(&q));
  end = clock();
  elapsed = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Elapsed time showing : %fs\n", elapsed);

  free_queue(&q);

  return 0;
}
