#include <vector>
#include <mutex>

#include "pool.hpp"
#include "connection.hpp"

// Pool Constructor
void ConnectionsPool::push_back (Connection conn) {
    std::lock_guard <std::mutex> lock(this->m);
    this->pool.push_back(conn);
}

// Remove closed connection
void ConnectionsPool::cleanClosedConnections () {
    std::lock_guard <std::mutex> lock(this->m);
    std::vector<Connection>::iterator current_connection = pool.begin(); 
    
    while (current_connection < pool.end()) {
        if (current_connection->is_open()) {
            current_connection++;
        } else {
            current_connection = pool.erase(current_connection);
        }
    }
}

Connection& ConnectionsPool::operator[](size_t idx) {
    std::lock_guard <std::mutex> lock(this->m);
    return this->pool[idx];
}

int ConnectionsPool::size() {
    std::lock_guard <std::mutex> lock(this->m);
    return this->pool.size();
}