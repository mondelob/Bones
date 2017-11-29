/* konet - Simple API providing a secure network interface
 * This file is under the MIT license
 */

#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

#include "konet.h"


int
_konet_socket(int port, char * bindaddr, int family, int backlog, const char ** err) {
  int s, retval;
  struct sockaddr_in addr;

  addr.sin_family = family;
  addr.sin_port = htons(port);
  // addr.sin_addr.s_addr = htonl(addr);

  if ((s = socket(family, SOCK_STREAM, 0)) < 0) {
    *err = strerror(errno);
    return -1;
  }

  if ((retval = bind(s, (struct sockaddr *)&addr, sizeof(addr))) < 0) {
    *err = strerror(errno);
    return -2;
  }

  if ((retval = listen(s, backlog)) < 0) {
    *err = strerror(errno);
    return -3;
  }

  return s;
}
/* Creates a socket and returns the file descriptor */

int
_konet_accept_handler(int sockfd, struct sockaddr_in * addr, const char ** err) {
  int s;
  unsigned int addrlen;

  addrlen = sizeof(*addr);

  if ((s = accept(sockfd, (struct sockaddr *)addr, &addrlen)) < 0) {
    *err = strerror(errno);
    return -1;
  }

  return s;
}
/* Handler to accept new connections and return the peer descriptor */

int
konet_tcp_socket(int port, char * bindaddr, int backlog, const char ** err) {
  return _konet_socket(port, bindaddr, AF_INET, backlog, err);
}
/* Creates a IPv4 socket and returns the file descriptor */

int
konet_async_server(int sockfd, const char ** err) {
  int s;
  struct sockaddr_in addr;

  while (1) {
    s = _konet_accept_handler(sockfd, &addr, err);
    if (s < 0)
      printf("Error handling connection : %s\n", *err);
    else
      printf("New connection added from : %s\n", inet_ntoa(addr.sin_addr));
  }

  return 0;
}
/* Runs an async server */
