#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <ctime>

#include "connection.hpp"

Connection::Connection(int socket, struct sockaddr_in address) {
    this->socket = socket;
    this->address = address;
    this->last_request = 0;
}

void Connection::close_connection() {
    if (this->is_open()) close(this->socket);
}

bool Connection::is_open() {
    unsigned char buffer;
    int received = recv(this->socket, &buffer, 1, MSG_PEEK | MSG_DONTWAIT);

    return received == 0 ? false : true;
}