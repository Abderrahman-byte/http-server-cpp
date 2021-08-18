#include <string>

#include "../http_parser/parser.hpp"
#include "../http_parser/utils.hpp"
#include "response.hpp"

Response::Response(int status, std::string body) {
    this->http_version = DEFAULT_VERSION;
    this->status_code = status;
    this->body = body;
}

Response::Response(std::string body) {
    this->http_version = DEFAULT_VERSION;
    this->status_code = DEFAULT_STATUS;
    this->body = body;
}

void Response::set_header(std::string name, std::string value) {
    int headers_count = this->headers.size();

    for (int i = 0; i < headers_count; i++) {
        http_header_t header = this->headers[i];

        if (header.name.compare(name) == 0) {
            this->headers[i].value = trim(value);
            return;
        }
    }

    http_header_t header;
    header.name = trim(name);
    header.value = trim(value);

    this->headers.push_back(header);
}

bool Response::has_header(std::string name) {
    int headers_count = this->headers.size();

    for (int i = 0; i < headers_count; i++) {
        http_header_t header = this->headers[i];

        if (header.name.compare(name) == 0) return true;
    }

    return false;
}

std::string Response::get_raw_headers() {
    std::string raw = "";
    int headers_count = this->headers.size();

    for(int i = 0; i < headers_count; i++) {
        http_header_t header = this->headers[i];

        if (trim(header.name).length() <= 0 ||
            trim(header.value).length() <= 0) continue;

        raw += trim(header.name);
        raw += ": ";
        raw += trim(header.value);
        raw += ENDLINE;
    }

    return raw;
}

void Response::set_default_headers() {
    http_header_t default_headers[] = {
        {"Content-Type", "text/html"},
        {"Connection", "Keep-alive"},
        {"Keep-Alive", "timeout=5"}
    };
    
    int headers_size = sizeof(default_headers) / sizeof(http_header_t);

    for (int i = 0; i < headers_size; i++) {
        http_header_t header = default_headers[i];

        if (!this->has_header(header.name)) {
            this->set_header(header.name, header.value);
        }
    }
}

std::string Response::get_raw() {
    std::string raw_response = "";
    int body_length;

    if (!check_http_version(this->http_version)) {
        this->http_version = DEFAULT_VERSION;
    }

    if (this->status_code < 100 || this->status_code >= 600) {
        this->status_code = DEFAULT_STATUS;
    }

    body_length = this->body.length();
    this->set_header("Content-Length", std::to_string(body_length));
    this->set_default_headers();

    raw_response += trim(this->http_version);
    raw_response += " ";
    raw_response += std::to_string(this->status_code);
    raw_response += " ";
    raw_response += status_code_to_text(this->status_code);
    raw_response += ENDLINE;
    raw_response += this->get_raw_headers();
    raw_response += ENDLINE;
    raw_response += body;

    return raw_response;
}

std::string Response::status_code_to_text(int status_code) {
    switch (status_code) {
        case 200:
            return "OK";
        
        case 404:
            return "NOT FOUND";

        default :
            return "NOT OK";
    }
}