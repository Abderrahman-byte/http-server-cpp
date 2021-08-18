#include <string>
#include <sstream>

#include <iostream>

#include "utils.hpp"
#include "parser.hpp"

// Http Request parser
void parse_http(IncomingMessage_t* message, char *buffer, int len) {
    std::stringstream butter_stream(std::string(buffer, len));
    std::string templine;
    bool end_headers = false;

    getline(butter_stream, message->method, ' ');
    getline(butter_stream, message->original_url, ' ');
    getline(butter_stream, message->http_version, '\n');

    message->http_version = trim(message->http_version);

    if (!check_http_method(message->method)) {
        throw "Unkown http method";
    }

    if (!check_http_version(message->http_version)) {
        throw "Unsupported version";
    }

    while(getline(butter_stream, templine, '\n')) {
        if (!end_headers && templine.length() == 1 && templine[0] == 0x0d) {
            end_headers = true;
        } 
        
        if (!end_headers) {
            http_header_t header;

            int sep_pos = templine.find(':');
            header.name = trim(templine.substr(0, sep_pos));
            header.value = trim(templine.substr(sep_pos + 1));

            message->http_headers.push_back(header);
        }

        if (end_headers && !(templine.length() == 1 && templine[0] == 0x0d)) {
            message->body += templine;
        }
    }
    
}