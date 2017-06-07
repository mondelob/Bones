/* 
 * ssl_server - Opens a socket server encrypted with SSL
 * Default port 10448
 * Usage: ssl_server [PORT]
 * Bruno Mondelo Giaramita
 * 2017-06-07
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
/* Socket includes */

#include <openssl/ssl.h>
#include <openssl/err.h>
/* OpenSSL includes */

#define PROGRAM_NAME "ssl_server"
/* The program official name */

#define SSL_CERTIFICATE "/var/tmp/ssl_server/ssl_server.cert.pem"
/* The SSL certificate */

#define SSL_KEY "/var/tmp/ssl_server/ssl_server.key.pem"
/* The SSL key */

#define MAX_DATA_SIZE 2048
/* The maximum buffer for message */

int
init_socket (int port)
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
  
  if ((new_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    fprintf(stderr, "%s - error allocating memory for socket\n",
      PROGRAM_NAME);
    return -1;
  }
  /* Allocate memory for the new socket */
  
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  /* Set the socket address variables */
  
  if (bind(new_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
    fprintf(stderr, "%s - error binding socket to port : %d\n",
      PROGRAM_NAME, port);
    return -2;
  }
  /* Bind the new socket */
  
  if (listen(new_socket, 1) < 0)
  {
    fprintf(stderr, "%s - error setting socket to listen\n", 
      PROGRAM_NAME);
    return -3;
  }
  /* Set socket to listening */
  
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
  
  if ((method = SSLv23_server_method()) == NULL) /* Deprecated */
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

int
configure_context (SSL_CTX * ctx)
{
  
  /*
   * Configures the SSL context
   * Input: SSL_CTX *
   * Output: void
  */
  
  if (SSL_CTX_use_certificate_file (ctx, SSL_CERTIFICATE, SSL_FILETYPE_PEM) != 1)
  {
    fprintf(stderr, "%s - error loading the SSL certificate from \
file : %s\n", PROGRAM_NAME, SSL_CERTIFICATE);
    fprintf(stderr, "Error stack:\n");
    ERR_print_errors_fp(stderr);
    return -1;
  }
  /* Set the certificate */
  
  if (SSL_CTX_use_PrivateKey_file (ctx, SSL_KEY, SSL_FILETYPE_PEM) != 1)
  {
    fprintf(stderr, "%s - error loading the SSL private key from \
file : %s\n", PROGRAM_NAME, SSL_KEY);
    fprintf(stderr, "Error stack:\n");
    ERR_print_errors_fp(stderr);
    return -2;
  }
  /* Set the key */
  
  return 0;
  
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
  
  int port;
  /* The port of the server */
  
  int mainsock;
  /* The main socket */
  
  int clientsock;
  /* The connected client socket */
  
  struct sockaddr_in clientaddr;
  /* The client address */
  
  uint addrlen;
  /* The address structure size */
  
  SSL_CTX * ctx;
  /* The SSL context */
  
  SSL * ssl;
  /* SSL structure for a new connection */
  
  char buf[MAX_DATA_SIZE];
  /* The received message buf */
  
  int bytes;
  /* Readed bytes */
  
  if (argc > 2)
  {
    fprintf(stderr, "%s - error, bad usage\n", PROGRAM_NAME);
    fprintf(stderr, "usage: %s [PORT]\n", PROGRAM_NAME);
    return -1;
  }
  else if (argc == 2)
  {
    port = atoi (argv[1]);
  }
  else
  {
    port = 10448;
  }
  /* Parse arguments. Assign the port of the server, by default if 
      no argument is passed is the 10448 */
  
  init_openssl ();
  /* Load the SSL service algorithm */
  
  if((ctx = create_context ()) == NULL)
    return 1;
  /* Create the SSL context */
  
  if (configure_context(ctx) != 0)
    return 2;
  /* Configure the new created context */
  
  if ((mainsock = init_socket (port)) < 0)
    return 3;
  printf("%s - openned socket via port : %d\n", PROGRAM_NAME, port);
  /* Create the new socket*/
  
  while (1)
  {
    
    printf("waiting for new connections...\n");
    
    addrlen = sizeof(clientaddr);
    /* Assign the length of the client address */
    
    if ((clientsock = accept(mainsock, (struct sockaddr *)&clientaddr,
      &addrlen)) < 0)
    {
      fprintf(stderr, "error handling new connection from : %s\n",
        inet_ntoa(clientaddr.sin_addr));
      continue;
    }
    printf("accepted new connection from : %s\n",
      inet_ntoa(clientaddr.sin_addr));
    /* Accept new connection */
    
    if ((ssl = SSL_new (ctx)) == NULL)
    {
      fprintf(stderr, "%s - error creating the SSL structure\n",
        PROGRAM_NAME);
      fprintf(stderr, "Error stack:\n");
      ERR_print_errors_fp(stderr);
      return 4;
    }
    /* Create the new SSL structure */
    
    if (SSL_set_fd (ssl, clientsock) != 1)
    {
      fprintf(stderr, "%s - error assigning the SSL to the client\n",
        PROGRAM_NAME);
      fprintf(stderr, "Error stack:\n");
      ERR_print_errors_fp(stderr);
      return 5;
    }
    /* Assign the SSL structure to the client descriptor */
    
    if (SSL_accept(ssl) != 1)
    {
      fprintf(stderr, "%s - error accepting the SSL connection\n",
        PROGRAM_NAME);
      fprintf(stderr, "Error stack:\n");
      ERR_print_errors_fp(stderr);
      continue;
    }
    /* Wait for client to start the TLS/SSL connection */
    
    while ((bytes = SSL_read(ssl, buf, sizeof(buf))) > 0)
    {
      
      buf[bytes] = '\0';
      /* Erase last character */
      
      printf("received message: %s\n", buf);
      printf("echoing back\n");
      buf[bytes] = '\n';
      /* Show message */
      
      if (SSL_write (ssl, buf, strlen(buf)) <= 0)
      {
        fprintf(stderr, "%s - error sending message to the SSL connection\n",
          PROGRAM_NAME);
        fprintf(stderr, "Error stack:\n");
        ERR_print_errors_fp(stderr);
        break;
      }
      /* Send message to client */
      
    }
    printf("closed connection to client : %s\n",
      inet_ntoa(clientaddr.sin_addr));
    /* Wait for a message and echo back the message till client closes 
        connection */
    
    SSL_free (ssl);
    /* Free SSL */
    
    close(clientsock);
    /* Close client */
    
  }
  /* Handle and send messages to all the new connections */
  
  close (mainsock);
  /* Close the socket */
  
  SSL_CTX_free (ctx);
  /* Free the context structure */
  
  cleanup_openssl ();
  /* Clean the cypher table */
  
  return 0;
  
}
