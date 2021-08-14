#include <netinet/in.h>
#include <unistd.h>

#include "connection.hpp"

void Connection::close_connection() {
    this->is_open = false;
    close(this->socket);
}

Connection::Connection(int socket, struct sockaddr_in address) {
    this->socket = socket;
    this->address = address;
    this->is_open = true;
}