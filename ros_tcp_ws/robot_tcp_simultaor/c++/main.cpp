#include "tcp_receive.h"

#define HOST_IP "192.168.1.169"
#define PORT 1234

int main(int argc, char**argv){

    int sockfd = connect_tcp(HOST_IP, PORT);

    return 0;
}