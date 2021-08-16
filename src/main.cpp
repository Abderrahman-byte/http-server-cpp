#include <thread>
#include <sys/socket.h>
#include <bits/refwrap.h>
#include <iostream>

#include "config.hpp"
#include "pool.hpp"
#include "connection.hpp"
#include "server.hpp"
#include "handleThread.hpp"


int main () {
    int server_socket;
    bool keep_alive = true; // whether to set SO_KEEPALIVE or not
    config_t config; // Configuration object
    ConnectionsPool connections; // Connections pool
    socklen_t address_len = sizeof(struct sockaddr_in);
    unsigned int accepted_connections = 0; // Keep tracking accepted_connections to implement round robin on threads

    init_config(&config); /* Initializing config object with default values */

    std::thread threads_pool[config.threads_cout];

    // Initialize threads
    for (int i = 0; i < config.threads_cout; i++) {
        threads_pool[i] = std::thread(handleThread, std::ref(connections), i, &config);
    }

    // Start server
    keep_alive = config.http_version.compare("HTTP/1.0") != 0;  // No SO_KEEPALIVE on http/1.0
    server_socket = start_server(config.address.c_str(), config.port, keep_alive);

    // Keep accepting new connections
    while (true) {
        connections.cleanClosedConnections();
        int ps = connections.size();
        std::cout << "[*] Size of pool " << ps << std::endl; 
        std::cout << "[*] Size of pool " << sizeof(Connection) * ps << std::endl; 

        struct sockaddr_in client_address;
        int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &address_len);

        Connection conn(client_socket, client_address);
        conn.worker_id = accepted_connections % config.threads_cout; 
        connections.push_back(conn);

        accepted_connections++;
        
        std::cout << "[*] Accepted connection num : " << accepted_connections << std::endl;
    }

    // Wait for threads to finish in case of interopt ?
    for (int i = 0; i < config.threads_cout; i++) threads_pool[i].join();

    return 0;
}