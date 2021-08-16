#include <string>

#ifndef _CONFIG_H_
#define _CONFIG_H_ 1

#define DEFAULT_PORT 8000
#define DEFAULT_ADDR "127.0.0.1"
#define DEFAULT_THREADS_COUNT 4
#define DEFAULT_KEEP_ALIVE_TIMEOUT 5
#define DEFAULT_KEEP_ALIVE_MAX_REQUEST 100
#define DEFAULT_STATIC_DIR "static"
#define DEFAULT_HTTP_VERSION "HTTP/1.1"
#define DEFAULT_SERVER_HEADER "Abderrahmane ELASRI"
#define DEFAULT_POWERED_BY_HEADER "C++"

typedef struct {
    int port;
    int threads_cout;
    int keep_alive_timeout;
    int keep_alive_max_requests;
    std::string address;
    std::string static_dir;
    std::string http_version;
    std::string header_server;
    std::string header_powered_by;
} config_t;

extern void init_config(config_t *) ;
extern void parse_config(config_t *, std::string) ;

#endif