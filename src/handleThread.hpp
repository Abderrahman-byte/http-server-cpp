#include <vector>

#include "connection.hpp"

#ifndef _HANDLETHREAD_H_
#define _HANDLETHREAD_H_

#define BUFFER_SIZE 1024

extern void handleThread (std::vector<Connection> &, int);
#endif