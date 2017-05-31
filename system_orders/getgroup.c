/* 
 * getgroup - Shows the group entry
 * Usage: getgroup [GROUPNAME]
 * Bruno Mondelo Giaramita
 * 2017-05-31
*/

#include <stdio.h>
#include <grp.h>

int
main (int argc, char * argv[])
{
  
  const char * groupname;
  /* The username to search */
  
  struct group * groupentry;
  /* The group structure */
  
  if (argc != 2)
  {
    fprintf(stderr, "getgroup: bad usage\n");
    fprintf(stderr, "usage: getgroup [GROUPNAME]\n");
    return -1;
  }
  /* Parse arguments */
  
  groupname = argv[1];
  /* Assign the username to the first argument */
  
  if ((groupentry = getgrnam(groupname)) == NULL)
  {
    fprintf(stderr, "getgroup: error retrieving group information\
for group '%s'\n", groupname);
    return 1;
  }
  /* Search for the group entry
     If it fails we return an error code and notify about this */

  printf("     Group name : %s\n", groupentry->gr_name);
  printf(" Group password : %s\n", groupentry->gr_passwd);
  printf("       Group ID : %d\n", groupentry->gr_gid);
  printf("          Users :\n");
  /* Show information */
  
  int i = 0;
  while (groupentry->gr_mem[i] != NULL)
  {
    printf("                  - %s\n", groupentry->gr_mem[i]);
    i++;
  }
  /* Show the users line per line */
  
  return 0;
  
}
