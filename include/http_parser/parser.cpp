#include <string>
#include <sstream>

#include <iostream>

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

// 
void parse_url(url_t* url, std::string unparsed_url) {
    int sep_pos = unparsed_url.find('?');
    std::string unparsed_query = "";

    if (sep_pos < 0) {
        url->path = unparsed_url;
        return ;
    }

    url->path = unparsed_url.substr(0, sep_pos);
    unparsed_query = unparsed_url.substr(sep_pos + 1);

    parse_search_query(&url->searchquery, unparsed_query);
}

//
void parse_search_query(std::vector<queryfield_t>* query, std::string unparsed_query) {
    std::string field_str;
    std::stringstream unparsed_query_stream(unparsed_query);

    while (getline(unparsed_query_stream, field_str, '&')) {
        int del_pos = field_str.find('=');
        queryfield_t field;

        if (del_pos >= 0) {
            field.name = trim(field_str.substr(0, del_pos));
            field.value = trim(field_str.substr(del_pos + 1));

            if (field.name.length() > 0 && field.value.length() > 0) {
                query->push_back(field);
            }
        }
    }
}

// Left Trim
std::string ltrim (std::string input_str) {
    size_t start = input_str.find_first_not_of(HTTP_WHITESPACE);
    return start == std::string::npos ? "" : input_str.substr(start);
}

// Right Trim
std::string rtrim (std::string input_str) {
    size_t end = input_str.find_last_not_of(HTTP_WHITESPACE);
    return end == std::string::npos ? "" : input_str.substr(0, end + 1);
}

// Trim White space
std::string trim (std::string input_str) {
    return ltrim(rtrim(input_str));
}

// Check if parsed http method is legit
bool check_http_method(std::string method) {
    std::string http_methods[] = {"GET", "POST", "HEAD", "PUT", "DELETE", "CONNECT", "TRACE", "OPTIONS", "PATCH"};
    size_t methods_count = sizeof(http_methods) / sizeof(http_methods[0]);

    for(int i = 0; i < methods_count; i++) {
        if (str_equal(http_methods[i], method)) return true;
    }

    return false;
}

// Check if version is support
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