#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <ctime>

#include "connection.hpp"

// Connection Constructor
Connection::Connection(int socket, struct sockaddr_in address) {
    this->socket = socket;
    this->address = address;
    this->last_request = 0;
}

// Close connection if it's open
void Connection::close_connection() {
    if (this->is_open()) close(this->socket);
}

// Check If Connection is open
bool Connection::is_open() {
    unsigned char buffer;

    // Try to recv data from socket if received 0 then the connection is closed
    int received = recv(this->socket, &buffer, 1, MSG_PEEK | MSG_DONTWAIT);  

    return received != 0;
}