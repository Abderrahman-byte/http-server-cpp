#include <string>

#include "utils.hpp"

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