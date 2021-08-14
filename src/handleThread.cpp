#include <unistd.h>
#include <vector>
#include <iostream>

#include "connection.hpp"
#include "handleThread.hpp"

void handleThread (std::vector<Connection> &connections, int i) {
    char buffer[BUFFER_SIZE];
    int received_len;

    while (true) {
        int connections_len = connections.size();

        for(int j = 0; j < connections_len; j++) {
            if (connections[j].worker_id != i || !connections[j].is_open) continue;
 
            received_len = recv(connections[j].socket, buffer, BUFFER_SIZE, MSG_DONTWAIT);
            
            if (received_len >= 0) {
                std::cout << "[*] From Thread [" << i << "] received : " << received_len << std::endl;
            } else {
                connections[j].close_connection();
            }
            
        }
    
       usleep(100000);
    }
}