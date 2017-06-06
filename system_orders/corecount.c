/* 
 * corecount - Counts the number of cores
 * Usage: corecount
 * Bruno Mondelo Giaramita
 * 2017-06-06
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>

int
main ()
{
  
  int cpucore;
  /* The number of cores */
  
  cpu_set_t cs;
  /* CPU structure */
  
  CPU_ZERO(&cs);
  /* Clear all old information */
  
  sched_getaffinity(0, sizeof(cs), &cs);
  /* Write the affinity mask */
  
  cpucore = 0;
  /* No core found at the moment */
  
  for (int i = 0; i < 8; i++)
    if (CPU_ISSET(i, &cs))
      cpucore++;
  /* Count the number of cores */
  
  printf("%d\n", cpucore);
  /* Show results */
  
  return 0;
  
}
