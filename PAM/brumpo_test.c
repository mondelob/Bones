/* 
 * pam_brumpo.so - shows a brumpo message for users:
   - mondelob
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>


PAM_EXTERN int
pam_sm_authenticate (pam_handle_t * pamh, int flags,
  int argc, const char ** argv)
{
 
  int retval;
  /* The value returned by function */
 
  const char * username;
  /* The string containing username */
  
  retval = pam_get_user (pamh, &username, "Username: ");
  /* Get the username */
  
  if (retval == PAM_SYSTEM_ERR)
  {
    fprintf(stderr, "PAM: error obtaining username\n");
    return PAM_AUTH_ERR;
  }
  /* Check for a null pointer return */
  
  if (retval != PAM_SUCCESS)
  {
    fprintf(stderr, "An error happened while obtaining username\n");
    return retval;
  }
  /* An error ocurred */
  
  if (strcmp(username, "mondelob") == 0)
    printf("You're BRUMPO!\n");
  else
    printf("Not even Brumpo...\n");
  /* Check for Brumpo */
  
  return PAM_SUCCESS;
  
}
