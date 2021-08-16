#include <string>

#include "http_parser/parser.hpp"
#include "response/response.hpp"
#include "connection.hpp"

#ifndef _HANDLE_REQUEST_
#define _HANDLE_REQUEST_

#define STATIC_DIR "./static"

extern void handleRequest(Connection&, IncomingMessage_t);
extern bool check_file_exists(std::string, struct stat*);
extern std::string join_path(std::string, std::string);
extern void serve_static(Response *, std::string);
extern void not_found(Response *);
extern std::string get_file_content(std::string);

#endif