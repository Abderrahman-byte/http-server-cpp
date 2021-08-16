#include <string>
#include <vector>

#include "../http_parser/parser.hpp"

#ifndef _RESPONSE_H_
#define _RESPONSE_H_

#define DEFAULT_STATUS 200
#define DEFAULT_VERSION "HTTP/1.1"
#define ENDLINE "\r\n"

class Response {
    public:
        int status_code;
        std::string http_version;
        std::string body;
        std::vector<http_header_t> headers;

        // Constructors
        Response(int = DEFAULT_STATUS, std::string = "");
        Response(std::string);

        void set_header(std::string, std::string);
        bool has_header(std::string);
        void set_default_headers();
        std::string get_raw_headers();
        std::string get_raw();

        static std::string status_code_to_text(int);
};

#endif
