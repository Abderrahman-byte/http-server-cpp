#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

#include "http_parser/parser.hpp"
#include "response/response.hpp"
#include "mime-types/mime.hpp"
#include "connection.hpp"
#include "handleRequest.hpp"
#include "utils.hpp"

void handleRequest(Connection& connection, IncomingMessage_t request) {
    Response response;
    url_t url;
    std::string response_str;
    std::string cwd(getcwd(NULL, 0));
    std::string requested_file;
    
    parse_url(&url, request.original_url);
    requested_file = join_path(join_path(cwd, STATIC_DIR), url.path);
    serve_static(&response, requested_file);

    response.set_header("Server", "Abderrhmane");
    response.set_header("X-Powered-By", "C++");
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