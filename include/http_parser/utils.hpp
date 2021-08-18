#include <string>

#ifndef _HTTP_PARSER_UTILS_H_
#define _HTTP_PARSER_UTILS_H_ 1

#define HTTP_WHITESPACE " \n\r\t\f\v"

extern std::string ltrim (std::string);
extern std::string rtrim (std::string);
extern std::string trim (std::string);
extern bool check_http_method(std::string);
extern bool check_http_version (std::string);
extern bool str_equal(std::string, std::string);

#endif