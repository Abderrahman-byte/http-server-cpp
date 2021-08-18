#include <vector>
#include <array>
#include <string>

#ifndef _HTTP_PARSER_H_
#define _HTTP_PARSER_H_ 1

typedef struct {
    std::string name;
    std::string value;
} http_header_t;

typedef struct {
    std::string method;
    std::string original_url;
    std::string http_version;
    std::vector<http_header_t> http_headers;

    std::string body;
} IncomingMessage_t;

extern void parse_http(IncomingMessage_t*, char *, int);

#endif