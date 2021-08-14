#include <unistd.h>
#include <vector>
#include <iostream>
#include <ctime>

#include "http_parser/parser.hpp"
#include "connection.hpp"
#include "handleThread.hpp"
#include "handleRequest.hpp"

void handleThread (std::vector<Connection> &connections, int i) {
    char buffer[BUFFER_SIZE];
    int received_len;

    while (true) {
        int connections_len = connections.size();

        for(int j = 0; j < connections_len; j++) {
            if (connections[j].worker_id != i || !connections[j].is_open()) continue;

            if (connections[j].last_request > 0 &&
                time(0) - connections[j].last_request >= KEEPALIVE_TIMEOUT) {
                connections[j].close_connection();
                continue;
            }

            received_len = recv(connections[j].socket, buffer, BUFFER_SIZE, MSG_DONTWAIT);
            
            if (received_len > 0) {
                IncomingMessage_t request;
                std::cout << "[*] From Thread [" << i << "] received : " << received_len << std::endl;
                
                parse_http(&request, buffer, BUFFER_SIZE);
                handleRequest(connections[i], request);
                connections[j].last_request = time(0);

                if (request.http_version.compare("HTTP/1.0") == 0) {
                    connections[j].close_connection();
                }
            }
        }
    
       usleep(SLEEP_TIME);
    }
}