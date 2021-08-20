#include <netinet/in.h>
#include <ctime>

#ifndef _CONNECTION_H_
#define _CONNECTION_H_ 1
class Connection {
    public :
        int socket;
        int worker_id;
        struct sockaddr_in address;
        time_t last_request ; // Used To track if Keep-alive timeout has passed
        int requests_count ; // Used To track if Keep-alive max-requests has passed

    // Methods 
        Connection(int, struct sockaddr_in);
        void close_connection();
        bool is_open();
}; // Connection
#endif