#include <string>
#include <vector>

#ifndef _HTTP_PARSER_URL_H_
#define _HTTP_PARSER_URL_H_ 1

typedef struct {
    std::string name;
    std::string value;
} queryfield_t ;

typedef struct {
    std::string path;
    std::vector<queryfield_t> searchquery;
} url_t;

extern void parse_url(url_t*, std::string);
extern void parse_search_query(std::vector<queryfield_t>*, std::string);

#endif