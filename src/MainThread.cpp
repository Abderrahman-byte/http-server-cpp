#include <iostream>

#include "config.hpp"
#include "pool.hpp"

void start_main_thread (int server_socket, ConnectionsPool &connections, config_t &config) {
    socklen_t address_len = sizeof(struct sockaddr_in);
    unsigned int accepted_connections = 0; // Keep tracking accepted_connections to implement round robin on thread
    
    // Keep accepting new incoming connections
    while (true) {
        connections.cleanClosedConnections();
        int ps = connections.size();
        std::cout << "[*] Size of pool " << ps << std::endl; 

        struct sockaddr_in client_address;
        int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &address_len);

        Connection conn(client_socket, client_address);
        conn.worker_id = accepted_connections % config.threads_cout; 
        connections.push_back(conn);

        accepted_connections++;
        
        std::cout << "[*] Accepted connection num : " << accepted_connections << std::endl;
    }   
}