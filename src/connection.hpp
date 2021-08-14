#include <netinet/in.h>
#include <ctime>

#ifndef _CONNECTION_H_
#define _CONNECTION_H_
class Connection {
    public :
        int socket;
        int worker_id;
        struct sockaddr_in address;
        time_t last_request ; // Keep-alive timeout

    // Methods 
        Connection(int, struct sockaddr_in);
        void close_connection();
        bool is_open();
};
#endif