#include <vector>
#include <array>
#include <string>

#ifndef _HTTP_PARSER_H_
#define _HTTP_PARSER_H_ 1

#define HTTP_WHITESPACE " \n\r\t\f\v"

typedef struct {
    std::string name;
    std::string value;
} http_header_t;

typedef struct {
    std::string name;
    std::string value;
} queryfield_t ;

typedef struct {
    std::string path;
    std::vector<queryfield_t> searchquery;
} url_t;

typedef struct {
    std::string method;
    std::string original_url;
    std::string http_version;
    std::vector<http_header_t> http_headers;

    std::string body;
} IncomingMessage_t;

extern void parse_http(IncomingMessage_t*, char *, int);
extern void parse_url(url_t*, std::string);
extern void parse_search_query(std::vector<queryfield_t>*, std::string);
extern std::string ltrim (std::string);
extern std::string rtrim (std::string);
extern std::string trim (std::string);
extern bool check_http_method(std::string);
extern bool check_http_version (std::string);
extern bool str_equal(std::string, std::string);

#endif