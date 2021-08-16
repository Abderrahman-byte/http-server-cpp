#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sstream>
#include <bits/basic_string.h>

#include "http_parser/parser.hpp"
#include "utils.hpp"
#include "config.hpp"

void init_config(config_t *config)  {
    std::string cwd(getcwd(NULL, 0));

    config->port = DEFAULT_PORT;//
    config->threads_cout = DEFAULT_THREADS_COUNT; //
    config->address = DEFAULT_ADDR; //
    config->http_version = DEFAULT_HTTP_VERSION; //
    config->keep_alive_timeout = DEFAULT_KEEP_ALIVE_TIMEOUT; //
    config->keep_alive_max_requests = DEFAULT_KEEP_ALIVE_MAX_REQUEST;
    config->header_server = DEFAULT_SERVER_HEADER; //
    config->header_powered_by = DEFAULT_POWERED_BY_HEADER; //

    config->static_dir = join_path(cwd, DEFAULT_STATIC_DIR);
}

void parse_config(config_t *config, std::string filename) {
    int fullpath_buffer_len = 100;
    char fullpath_buffer[fullpath_buffer_len];
    std::string fullpath(realpath(filename.c_str(), fullpath_buffer));
    struct stat config_file_stat;

    std::stringstream config_content;
    std::string templine;

    if (!check_file_exists(fullpath, &config_file_stat)) {
        throw "Config file doesn\'t exist";
    }

    if (config_file_stat.st_mode & S_IFDIR) {
        throw "Config path is a directory";
    }

    config_content = std::stringstream(get_file_content(fullpath));

    while (getline(config_content, templine)) {
        templine = trim(templine);

        if (templine.length() > 0) {
            add_config_line(config, templine);
        }
    }
}

/* Add config directive to config object */
void add_config_line(config_t *config, std::string line) {
    int sep_pos = line.find("=");
    int hash_pos = line.find("#");
    std::string name, value;
    int value_int;

    if (sep_pos <= 0 || sep_pos >= line.length() - 1 ||
    hash_pos == 0) return ;

    name = line.substr(0, sep_pos);
    value = line.substr(sep_pos + 1);

    if (value.compare("NULL") == 0) {
        value = "";
    }

    if (name.compare("address") == 0 && check_ip_address(value)) {
        config->address = value;
        return;
    }

    if (name.compare("http_version") == 0 && check_http_version(value)) {
        config->http_version = value;
        return;
    }

    if (name.compare("header_powered_by") == 0) {
        config->header_powered_by = value;
        return;
    }

    if (name.compare("header_server") == 0) {
        config->header_server = value;
        return;
    }

    try {
        value_int = stoi(value);
    } catch (...) { return ; }

    if (name.compare("threads_count") == 0) {
        if (value_int >= 1 && value_int <= 10) {
            config->threads_cout = value_int;
        }
        return ;
    }

    if (name.compare("port") == 0) {
        if (value_int > 0) config->port = value_int;
        return ;
    }

    if (name.compare("keep_alive_timeout") == 0) {
        if (value_int > 0 ) config->keep_alive_timeout = value_int;
        return ;
    }

    if (name.compare("keep_alive_max_requests") == 0) {
        if (value_int > 0) config->keep_alive_max_requests;
    }

}