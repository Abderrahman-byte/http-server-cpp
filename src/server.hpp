#include <arpa/inet.h>

#ifndef _SERVER_H_
#define _SERVER_H_

#define DEFAULT_PORT 8000
#define DEFAULT_ADDR "127.0.0.1"

extern int start_server(const char* = DEFAULT_ADDR, int = DEFAULT_PORT);
extern struct sockaddr_in make_addr_port(const char*, int);

#endif