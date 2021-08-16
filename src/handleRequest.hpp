#include <string>

#include "http_parser/parser.hpp"
#include "response/response.hpp"
#include "config.hpp"
#include "connection.hpp"

#ifndef _HANDLE_REQUEST_
#define _HANDLE_REQUEST_ 1

extern void handleRequest(Connection&, IncomingMessage_t, config_t*);
extern void serve_static(Response *, std::string);
extern void not_found(Response *);

#endif