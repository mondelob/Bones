/* 
 * getshadow - Shows the shadow entry
 * Usage: getshadow [USERNAME]
 * Bruno Mondelo Giaramita
 * 2017-05-31
*/

#include <stdio.h>
#include <shadow.h>
#include <time.h>

int
main (int argc, char * argv[])
{

  const char * username;
  /* The username to search */
  
  struct spwd * userentry;
  /* The shadow structure */
  
  if (argc != 2)
  {
    fprintf(stderr, "getshadow: bad usage\n");
    fprintf(stderr, "usage: getshadow [USERNAME]\n");
    return -1;
  }
  /* Parse arguments */
  
  username = argv[1];
  /* Assign the username to the first argument */
  
  if ((userentry = getspnam(username)) == NULL)
  {
    fprintf(stderr, "getshadow: error retrieving shadow information\
for user '%s'\n", username);
    return 1;
  }
  /* Search for the shadow entry
     If it fails we return an error code and notify about this */

  printf("           Username : %s\n", userentry->sp_namp);
  printf("           Password : %s\n", userentry->sp_pwdp);
  printf("        Last change : %s", ctime(&userentry->sp_lstchg));
  printf("           Min days : %d\n", userentry->sp_min);
  printf("           Max days : %d\n", userentry->sp_max);
  printf("       Warning days : %d\n", userentry->sp_warn);
  printf("      Inactive days : %d\n", userentry->sp_inact);
  printf(" Account expiration : %s", ctime(&userentry->sp_expire));
  /* Show information */
  
  return 0;
  
}
