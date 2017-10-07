/* 
 * writeuser - Writes a file containing the username
 * Usage: writeuser FILE
          writeuser -u|--uid FILE
          writeuser -n|--username FILE
 * Bruno Mondelo Giaramita
 * 2017-06-06
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <pwd.h>

static struct option long_options [] = {
  {"help", no_argument, NULL, 'h'},
	{"uid", required_argument, NULL, 'u'},
	{"username", required_argument, NULL, 'n'},
	{NULL, 0, NULL, 0}
};
/* Arguments long options */

void
usage (int status)
{
  
  
  
}

uid_t
get_uid (char * username)
{
  
  /*
   * Function to return the uid of a user
   * Input: char *
   * Output: uid_t
  */
  
  uid_t user_id;
  /* The user uid */
  
  struct passwd * userentry;
  /* The passwd structure */
  
  if ((userentry = getpwnam(username)) == NULL)
    return -1;
  /* Search for the user id, if not found return a -1 */
  
  user_id = userentry->pw_uid;
  /* Get the UID */
  
  return user_id;
  
}

char *
get_username (uid_t user_id)
{
  
  /*
   * Function to return the username of a user
   * Input: uid_t
   * Output: char *
  */
  
  char * username;
  /* The user name */
  
  struct passwd * userentry;
  /* The passwd structure */
  
  if ((userentry = getpwnam(username)) == NULL)
    return NULL;
  /* Search for the user id, if not found return a NULL */
  
  username = userentry->pw_name;
  /* Get the username */
  
  return username;
  
}

int
main (int argc, char * argv[])
{
  
  char * filename;
  /* The file to write */
  
  uid_t user_id;
  /* The user ID */
  
  char * username;
  /* The username */
  
  user_id = -1;
  username = NULL;
  /* Set username and UID to null values to only use one of them */
  
  int opt;
  /* The parsed argument */
  
  while ((opt = getopt_long(argc, argv, "hu:n:", long_options, NULL)) != -1)
  {
    switch (opt)
    {
      case 'h':
        usage(EXIT_SUCCESS);
        break;
      case 'u':
        if (username != NULL)
        {
          fprintf(stderr, "writeuser - Bad usage\n");
          usage(EXIT_FAILURE);
        }
        else {
          user_id = atoi(optarg);
        }
        break;
      case 'n':
        if (user_id != -1)
        {
          fprintf(stderr, "writeuser - Bad usage\n");
          usage(EXIT_FAILURE);
        }
        else {
          username = optarg;
        }
        break;
      default:
        printf("writeuser - Bad usage\n");
        usage(EXIT_FAILURE);
        break;
    }
  }
  /* Parse arguments */
  
  if (username == NULL && user_id == -1)
    user_id = getuid();
  /* No specified username and uid execute by own */
  
  if (username != NULL)
    if ((user_id = get_uid(username)) == -1)
    {
      fprintf(stderr, "writeuser - error, user '%s' not found\n",
        username);
      return 1;
    }
  /* Got username we must search for UID */
  
  else if (user_id != -1)
    if ((username = get_username(user_id)) == NULL)
    {
      fprintf(stderr, "writeuser - error, user with uid '%d' not found\n",
        user_id);
      return 1;    
    }
  /* Got user id we must search for username */
  
  printf("The UID is : %d and the user: %s\n", user_id, username);
  
  return 0;
  
}
