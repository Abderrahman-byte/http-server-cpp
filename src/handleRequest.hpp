#include "http_parser/parser.hpp"
#include "connection.hpp"

#ifndef _HANDLE_REQUEST_
#define _HANDLE_REQUEST_
extern void handleRequest(Connection, IncomingMessage_t);
#endif