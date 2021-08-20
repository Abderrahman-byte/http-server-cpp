#include <thread>
#include <bits/refwrap.h>
#include <iostream>
#include <exception>

#include "config.hpp"
#include "pool.hpp"
#include "utils.hpp"
#include "connection.hpp"
#include "server.hpp"
#include "handleThread.hpp"
#include "MainThread.hpp"


int main (int argc, char **argv) {
    int server_socket; // Server Socket Fd
    ConnectionsPool connections; // Connections pool
    config_t config; // Configuration object
    bool keep_alive = true; // whether to set SO_KEEPALIVE or not
    std::string config_filename;

    parse_args(argc, argv, config_filename);

    try {
        init_config(&config); /* Initializing config object with default values */
        if (config_filename.length() > 0) {
            parse_config(&config, config_filename); /* Parse Configuration from config file */
        }
    } catch (const char *err) {
        std::cerr << "[CONFIG ERROR] " << err << std::endl;
        exit(EXIT_FAILURE);
    } catch (const std::exception &e) {
        std::cerr << "[CONFIG ERROR] " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    std::thread threads_pool[config.threads_cout]; /* Array Of Workers Threads */

    // Initialize threads
    for (int i = 0; i < config.threads_cout; i++) {
        threads_pool[i] = std::thread(handleThread, std::ref(connections), i, &config);
    }

    keep_alive = config.http_version.compare("HTTP/1.0") != 0;  // No SO_KEEPALIVE on http/1.0

    try {
        // Server Starts listening here
        server_socket = start_server(config.address.c_str(), config.port, keep_alive);
        std::cout << "[*] Server is listening " << config.address << ":" << config.port << std::endl;
    } catch (const char *err) {
        std::cerr << "[ERROR STARTING SERVER] " << err << std::endl;
        exit(EXIT_FAILURE);
    } catch (const std::exception &e) {
        std::cerr << "[ERROR STARTING SERVER] " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Start the main thread that Accept new connections
    start_main_thread(server_socket, connections, config);

    // Wait for threads to finish in case of interopt ?
    for (int i = 0; i < config.threads_cout; i++) threads_pool[i].join();

    return 0;
}