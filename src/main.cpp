#include <thread>
#include <sys/socket.h>
#include <bits/refwrap.h>
#include <iostream>

#include "connection.hpp"
#include "server.hpp"
#include "handleThread.hpp"

#define THREADS_COUNT 10

int main () {
    int server_socket = start_server();
    std::vector<Connection> connections;
    std::thread threads_pool[THREADS_COUNT];

    unsigned int accepted_connections = 0;
    socklen_t address_len = sizeof(struct sockaddr_in);

    // Initialize threads
    for (int i = 0; i < THREADS_COUNT; i++) {
        threads_pool[i] = std::thread(handleThread, std::ref(connections), i);
    }

    // Accept new connections
    while (true) {
        struct sockaddr_in client_address;
        int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &address_len);

        Connection conn(client_socket, client_address);
        conn.worker_id = accepted_connections % THREADS_COUNT;
        connections.push_back(conn);

        accepted_connections++;

        // std::cout << "accepted connection num : " << accepted_connections << std::endl;
    }

    // Wait for threads to finish in case of interopt ?
    for (int i = 0; i < THREADS_COUNT; i++) threads_pool[i].join();

    return 0;
}