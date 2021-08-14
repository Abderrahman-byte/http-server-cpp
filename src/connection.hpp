#include <netinet/in.h>

#ifndef _CONNECTION_H_
#define _CONNECTION_H_
class Connection {
    public :
        int socket;
        int worker_id;
        bool is_open = false;
        struct sockaddr_in address;
        
        Connection(int, struct sockaddr_in);
        void close_connection();
};
#endif