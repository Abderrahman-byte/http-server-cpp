#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "server.hpp"
#include "http_parser/parser.hpp"

#define BUFFER_SIZE 1024

int main () {
    int server_socket = start_server();

    while (1) {
        IncomingMessage_t request ;
        char buffer[BUFFER_SIZE];

        struct sockaddr_in client_address;
        unsigned int client_address_len = sizeof(client_address);

        int client_socket = accept(server_socket, (sockaddr *)&client_address, &client_address_len);

        int received_len = recv(client_socket, buffer, BUFFER_SIZE, 0);

        std::cout << "[*] Received : " << received_len << "\n";

        try {
            parse_http(&request, buffer, received_len);
        } catch(const char* e) {
            std::cout << "[ERROR] : " << e << '\n';
        }

        close(client_socket);
    }
    
    return 0;
}