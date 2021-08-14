#include <vector>

#include "connection.hpp"

#ifndef _HANDLETHREAD_H_
#define _HANDLETHREAD_H_

#define KEEPALIVE_TIMEOUT 5
#define SLEEP_TIME 100000
#define BUFFER_SIZE 1024

extern void handleThread (std::vector<Connection> &, int);
#endif