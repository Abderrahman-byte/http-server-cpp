#include <string>
#include <sstream>

#include "parser.hpp"

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

            header.name = templine.substr(0, sep_pos);
            header.value = templine.substr(sep_pos + 1);

            header.name = trim(header.name);
            header.value = trim(header.value);

            message->http_headers.push_back(header);
        }

        if (end_headers && !(templine.length() == 1 && templine[0] == 0x0d)) {
            message->body += templine;
        }
    }
    
}

std::string ltrim (std::string input_str) {
    size_t start = input_str.find_first_not_of(HTTP_WHITESPACE);
    return start == std::string::npos ? "" : input_str.substr(start);
}

std::string rtrim (std::string input_str) {
    size_t end = input_str.find_last_not_of(HTTP_WHITESPACE);
    return end == std::string::npos ? "" : input_str.substr(0, end + 1);
}

std::string trim (std::string input_str) {
    return ltrim(rtrim(input_str));
}

bool check_http_method(std::string method) {
    std::string http_methods[] = {"GET", "POST", "HEAD", "PUT", "DELETE", "CONNECT", "TRACE", "OPTIONS", "PATCH"};
    size_t methods_count = sizeof(http_methods) / sizeof(http_methods[0]);

    for(int i = 0; i < methods_count; i++) {
        if (str_equal(http_methods[i], method)) return true;
    }

    return false;
}

bool check_http_version (std::string version) {
    std::string http_supported_version[] = {"HTTP/1.1", "HTTP/1.0"};
    size_t version_count = sizeof(http_supported_version) / sizeof(http_supported_version[0]);

    for(int i = 0; i < version_count; i++) {
        if (str_equal(http_supported_version[i], version)) return true;
    }

    return false;
}

bool str_equal(std::string first, std::string second) {
    return first.compare(second) == 0;
}