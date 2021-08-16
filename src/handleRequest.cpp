#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>

#include "http_parser/parser.hpp"
#include "response/response.hpp"
#include "connection.hpp"
#include "handleRequest.hpp"

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

    send(connection.socket, response_str.c_str(), response_str.length(), MSG_DONTWAIT);
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
        response->status_code = 200;
        response->set_header("Content-Type", "text/html");
        response->body = get_file_content(filename);  
    } else not_found(response);
}

void not_found(Response *response) {
    response->status_code = 404;
    response->set_header("Content-Type", "text/plain");
    response->body = "File doesn\'t exist";  
}

bool check_file_exists(std::string filename, struct stat* file_stat) {
    if (file_stat != NULL) {
        return stat(filename.c_str(), file_stat) == 0;
    }

    struct stat filestat;
    return stat(filename.c_str(), &filestat) == 0;
}

std::string join_path(std::string parent, std::string child) {
    int path_start = child.find_first_not_of("./");
    parent = parent.substr(0, parent.find_last_not_of("/") + 1);

    if (path_start > 0 && path_start < child.length()) {
        child = child.substr(child.find_first_not_of("./"));
    } else if (path_start >= child.length()) {
        child = "";
    }

    return parent + "/" + child;
}

std::string get_file_content(std::string filename) {
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string content;
        std::string templine;

        while(getline(file, templine)) {
            content += templine + "\n";
        }

        file.close();

        return content;
    }

    return "";
}