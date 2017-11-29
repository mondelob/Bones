/* konet - Simple API providing a secure network interface
 * This file is under the MIT license
 */

#ifndef KONET_H
#define KONET_H

int konet_tcp_socket(int port, char * bindaddr, int backlog, const char ** err);
/* Creates a IPv4 socket and returns the file descriptor */

int konet_async_server(int s, const char ** err);
/* Runs an async server */

#endif
