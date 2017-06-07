/* 
 * ssl_client - Reads all the CA from a socket TLS/SSL
 * Usage: ssl_client HOST PORT
 * Bruno Mondelo Giaramita
 * 2017-06-07
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netdb.h>
/* Socket includes */

#include <openssl/ssl.h>
#include <openssl/err.h>
/* OpenSSL includes */

#define PROGRAM_NAME "ssl_client"
/* The program official name */

#define MAX_DATA_SIZE 2048
/* The maximum buffer for message */

int
init_socket (const char * hostname, int port)
{
  
  /*
   * Creates a new socket
   * Input: int
   * Output: int (socket descriptor)
  */
  
  int new_socket;
  /* The new socket to create */
  
  struct sockaddr_in addr;
  /* The socket address */
  
  struct hostent * host;
  /* The server host */
  
  if ((new_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
  {
    fprintf(stderr, "%s - error allocating memory for socket\n",
      PROGRAM_NAME);
    return -1;
  }
  /* Allocate memory for the new socket */
  
  if ((host = gethostbyname(hostname)) == NULL)
  {
    fprintf(stderr, "%s - error getting host information : %s\n",
      PROGRAM_NAME, hostname);
    return -2;
  }
  /* Get the host structure */
  
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = *(long*)(host->h_addr);
  /* Set the socket address variables */
  
  if (connect(new_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
    fprintf(stderr, "%s - error connecting to host %s via port : %d\n",
      PROGRAM_NAME, hostname, port);
    return -2;
  }
  /* Connect to the new socket */
  
  return new_socket;
  
}

int
init_openssl (void)
{
  
  /*
   * Function to load the SSL service
   * Input: void
   * Output: void
  */
  
  SSL_load_error_strings ();
  /* Free and load the error strings */
  
  SSL_library_init ();
  /* Initzialize the algorithm library */
  
  OpenSSL_add_all_algorithms ();
  /* Add algorithms to internal table */
  
}

SSL_CTX *
create_context (void)
{
  
  /*
   * Creathe the SSL context structure
   * Input: void
   * Output: SSL_CTX *
  */
  
  const SSL_METHOD * method;
  /* The SSL method structure */
  
  SSL_CTX * ctx;
  /* The SSL context structure */
  
  if ((method = SSLv23_client_method()) == NULL) /* Deprecated */
  {
    fprintf(stderr, "%s - error creating the SSL method structure\n",
      PROGRAM_NAME);
    fprintf(stderr, "Error stack:\n");
    ERR_print_errors_fp(stderr);
    return NULL;
  }
  /* Create the method structure, not creating it is a fatal error */
  
  if ((ctx = SSL_CTX_new (method)) == NULL)
  {
    fprintf(stderr, "%s - error creating the SSL context structure\n",
      PROGRAM_NAME);
    fprintf(stderr, "Error stack:\n");
    ERR_print_errors_fp(stderr);
    return NULL;
  }
  /* Create the SSL context structure, not creating it is a fatal
      error */
      
  return ctx;
  
}

void
cleanup_openssl (void)
{
  
  /*
   * Cleans all the table
   * Input: void
   * Output: void
  */
  
  EVP_cleanup ();
  /* Remove all cyphers from the table */
  
}

int
main (int argc, char * argv[])
{
  
  char * hostname;
  /* The hostname of the server */
  
  int port;
  /* The port of the server */
  
  int mainsock;
  /* The main socket */
  
  SSL_CTX * ctx;
  /* The SSL context */
  
  SSL * ssl;
  /* SSL structure for a new connection */
  
  char userinput[MAX_DATA_SIZE];
  /* The user input */
  
  char buf[MAX_DATA_SIZE];
  /* The received message buf */
  
  int bytes;
  /* Readed bytes */
  
  if (argc != 3)
  {
    fprintf(stderr, "%s - error, bad usage\n", PROGRAM_NAME);
    fprintf(stderr, "usage: %s HOST PORT\n", PROGRAM_NAME);
    return -1;
  }
  hostname = argv[1];
  port = atoi(argv[2]);
  /* Parse arguments */
  
  init_openssl ();
  /* Load the SSL service algorithm */
  
  if((ctx = create_context ()) == NULL)
    return 1;
  /* Create the SSL context */
  
  if ((mainsock = init_socket (hostname, port)) < 0)
    return 2;
  printf("%s - connected to host %s via port : %d\n", PROGRAM_NAME,
    hostname, port);
  /* Create the new socket*/
  
  if ((ssl = SSL_new (ctx)) == NULL)
  {
    fprintf(stderr, "%s - error creating the SSL structure\n",
      PROGRAM_NAME);
    fprintf(stderr, "Error stack:\n");
    ERR_print_errors_fp(stderr);
    return 3;
  }
  /* Create the new SSL structure */
  
  if (SSL_set_fd (ssl, mainsock) != 1)
  {
    fprintf(stderr, "%s - error assigning the SSL to the client\n",
      PROGRAM_NAME);
    fprintf(stderr, "Error stack:\n");
    ERR_print_errors_fp(stderr);
    return 4;
  }
  /* Assign the SSL structure to the client descriptor */
  
  if (SSL_connect (ssl) != 1)
  {
    fprintf(stderr, "%s - error connecting to the SSL server\n",
      PROGRAM_NAME);
    fprintf(stderr, "Error stack:\n");
    ERR_print_errors_fp(stderr);
    return 5;
  }
  /* Connect to the SSL server */
  
  while (1)
  {
    
    printf("> ");
    /* Show prompt */
    
    scanf("%s", userinput);
    /* Read user input */
    
    if (SSL_write (ssl, userinput, strlen(userinput)) <= 0)
    {
      fprintf(stderr, "%s - error sending message to the SSL connection\n",
        PROGRAM_NAME);
      fprintf(stderr, "Error stack:\n");
      ERR_print_errors_fp(stderr);
      break;
    }
    /* Send message to server */
    
    if ((bytes = SSL_read(ssl, buf, sizeof(buf))) <= 0)
    {
      fprintf(stderr, "%s - error receiving message from the server\n",
        PROGRAM_NAME);
      fprintf(stderr, "Error stack:\n");
      ERR_print_errors_fp(stderr);
      return 6;
    }
    /* Receive the message and decrypt it */
    
    buf[bytes - 1] = '\0';
    /* Erase last character */
    
    printf("Received message : %s\n", buf);
    /* Show message */
    
  }
  /* Stay sending messages */
  
  SSL_free (ssl);
  /* Free SSL */
  
  close (mainsock);
  /* Close the socket */
  
  SSL_CTX_free (ctx);
  /* Free the context structure */
  
  cleanup_openssl ();
  /* Clean the cypher table */
  
  return 0;
  
}
