#include <unistd.h>
#include <vector>
#include <iostream>
#include <ctime>

#include "http_parser/parser.hpp"
#include "config.hpp"
#include "connection.hpp"
#include "pool.hpp"
#include "handleThread.hpp"
#include "handleRequest.hpp"

void handleThread (ConnectionsPool &connections, int i, config_t *config) {
    char buffer[BUFFER_SIZE];
    int received_len;

    while (true) {
        int connections_len = connections.size();

        for(int j = 0; j < connections_len; j++) {
            Connection& connection = connections[j];

            if (connection.worker_id != i || !connection.is_open()) continue;

            // Check if keep-alive timeout of a connection is passed
            if (connection.last_request > 0 &&
                time(0) - connection.last_request >= config->keep_alive_timeout) {
                connection.close_connection();
                continue;
            }

            received_len = recv(connection.socket, buffer, BUFFER_SIZE, MSG_DONTWAIT);
            
            if (received_len > 0) {
                IncomingMessage_t request;
                
                parse_http(&request, buffer, BUFFER_SIZE); // parse http request
                handleRequest(connection, request, config); // handle parsed request
                connection.last_request = time(0);

                // Close connection after response if protocol version is 1.0
                if (request.http_version.compare("HTTP/1.0") == 0 ||
                config->http_version.compare("HTTP/1.0") == 0) {
                    connection.close_connection();
                }
            }
        }
    
       usleep(SLEEP_TIME);
    }
}