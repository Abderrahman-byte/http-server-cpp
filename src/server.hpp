#include <arpa/inet.h>

#ifndef _SERVER_H_
#define _SERVER_H_ 1

#define DEFAULT_PORT 8000
#define DEFAULT_ADDR "127.0.0.1"
#define DEFAULT_KEEP_ALIVE true

extern int start_server(const char* = DEFAULT_ADDR, int = DEFAULT_PORT, bool = DEFAULT_KEEP_ALIVE);
extern struct sockaddr_in make_addr_port(const char*, int);
extern int set_SO_REUSEADDR(int);
extern int set_SO_KEEPALIVE(int);

#endif