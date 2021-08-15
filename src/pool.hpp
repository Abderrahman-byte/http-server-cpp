#include <vector>
#include <mutex>

#include "connection.hpp"

#ifndef _CONNECTION_POOL_H_
#define _CONNECTION_POOL_H_

class ConnectionsPool {
    public :
        std::vector<Connection> pool;
        std::mutex m;

        void push_back(Connection);
        void cleanClosedConnections();
        int size();

        Connection& operator[] (size_t);
};

#endif