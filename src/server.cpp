// THIS CODE WORKS ONLY ON UNIX SYSTEMS 
// MUST ADD WINDOWS SUPPORT

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "server.hpp"

// Start a tcp server and return socket fd
int start_server(const char* addr, int port, bool keep_alive) {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    int option_value = 1;
    struct sockaddr_in server_address = make_addr_port(addr, port);

    if (set_SO_REUSEADDR(server_socket) < 0) {
        throw "Could\'t set socket SO_REUSEADDR option";
    }

    if (keep_alive) {
        if (set_SO_KEEPALIVE(server_socket) < 0) {
            throw "Could\'t set socket SO_KEEPALIVE option";
        }
    }

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address))) {
        throw "Could\'t bind socket with address";
    }

    if (listen(server_socket, 5)) {
        throw "Could\'t listen";
    }

    return server_socket;
}

// Make sockaddr_in from address and port
struct sockaddr_in make_addr_port(const char *addr, int port) {
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(addr);
    address.sin_port = htons(port);

    return address;
}

// Set SO_REUSEADDR OPTION
int set_SO_REUSEADDR(int socket) {
    int option_value = 1;
    return setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (void*)&option_value, sizeof(option_value));
}

// Set SO_KEEPALIVE OPTION
int set_SO_KEEPALIVE(int socket) {
    int option_value = 1;
    return setsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, (void*)&option_value, sizeof(option_value));
}