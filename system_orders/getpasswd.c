/* 
 * getpasswd - Shows the passwd entry
 * Usage: get_passwd [USERNAME]
 * Bruno Mondelo Giaramita
 * 2017-05-31
*/

#include <stdio.h>
#include <pwd.h>

int
main (int argc, char * argv[]) {
  
  const char * username;
  /* The username to search */
  
  struct passwd * userentry;
  /* The passwd structure */
  
  if (argc != 2)
  {
    fprintf(stderr, "getpasswd: bad usage\n");
    fprintf(stderr, "usage: getpasswd [USERNAME]\n");
    return -1;
  }
  /* Parse arguments */
  
  username = argv[1];
  
  if ((userentry = getpwnam(username)) == NULL)
  {
    fprintf(stderr, "getpasswd: error retrieving passwd information\
for user '%s'\n", username);
    return 1;
  }
  /* Search for the passwd entry
     If it fails we return an error code and notify about this */
  
  printf(" Username : %s\n", userentry->pw_name);
  printf(" Password : %s\n", userentry->pw_passwd);
  printf("  User ID : %d\n", userentry->pw_uid);
  printf(" Group ID : %d\n", userentry->pw_gid);
  printf("    GECOS : %s\n", userentry->pw_gecos);
  printf("  Homedir : %s\n", userentry->pw_dir);
  printf("    Shell : %s\n", userentry->pw_shell);
  /* Show results */
  
  return 0;

}
