#include <unistd.h>

#include "http_parser/parser.hpp"
#include "http_parser/url.hpp"
#include "response/response.hpp"
#include "config.hpp"
#include "mime-types/mime.hpp"
#include "connection.hpp"
#include "handleRequest.hpp"
#include "utils.hpp"

void handleRequest(Connection& connection, IncomingMessage_t request, config_t *config) {
    Response response;
    url_t url;
    std::string response_str;
    std::string cwd(getcwd(NULL, 0));
    std::string requested_file;

    if (request.method.compare("GET") == 0) {
        parse_url(&url, request.original_url);
        requested_file = join_path(config->static_dir, url.path);
        serve_static(&response, requested_file);
    }
    
    if (config->http_version.compare("HTTP/1.1") == 0 &&
    request.http_version.compare("HTTP/1.1") == 0) {
        response.set_header("Connection", "Keep-alive");
        response.set_header("Keep-Alive", "timeout=" + std::to_string(config->keep_alive_timeout));
        response.http_version = "HTTP/1.1";
    } else {
        response.set_header("Connection", "Close");
        response.http_version = "HTTP/1.0";
    }

    if (config->header_server.length() > 0) {
        response.set_header("Server", config->header_server);
    }

    if (config->header_powered_by.length() > 0) {
        response.set_header("X-Powered-By", config->header_powered_by);
    }

    response_str = response.get_raw();

    send(connection.socket, response_str.c_str(), response_str.length(), 0);
}

void serve_static(Response *response, std::string filename) {
    struct stat filestat;
    bool file_exists = check_file_exists(filename, &filestat);

    if (!file_exists) {
        not_found(response);
        return ;
    } 
    
    if (filestat.st_mode & S_IFDIR) {
        serve_static(response, join_path(filename, "index.html"));
    } else if (filestat.st_mode & S_IFREG) {
        std::string ext = get_file_extension(filename);
        response->status_code = 200;
        response->set_header("Content-Type", get_mime_type(ext));
        response->body = get_file_content(filename);  
    } else not_found(response);
}

void not_found(Response *response) {
    response->status_code = 404;
    response->set_header("Content-Type", "text/plain");
    response->body = "File doesn\'t exist";
}