#include <iostream>
#include <unistd.h>

#include "utils.hpp"
#include "config.hpp"

void init_config(config_t *config)  {
    std::string cwd(getcwd(NULL, 0));

    config->port = DEFAULT_PORT;
    config->threads_cout = DEFAULT_THREADS_COUNT;
    config->address = DEFAULT_ADDR;
    config->http_version = DEFAULT_HTTP_VERSION;
    config->keep_alive_timeout = DEFAULT_KEEP_ALIVE_TIMEOUT;
    config->keep_alive_max_requests = DEFAULT_KEEP_ALIVE_MAX_REQUEST;
    config->header_server = DEFAULT_SERVER_HEADER;
    config->header_powered_by = DEFAULT_POWERED_BY_HEADER;

    config->static_dir = join_path(cwd, DEFAULT_STATIC_DIR);
}