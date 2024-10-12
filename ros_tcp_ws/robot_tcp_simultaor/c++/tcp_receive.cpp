#include "tcp_receive.h"

int connect_tcp(const char *ip, int port)
{
    int sockfd;
    struct sockaddr_in serv_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        CUSTOM_ERROR("ERROR opening socket");
        return -1;
    }
    CUSTOM_LOG("Socket created");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_aton(ip, &serv_addr.sin_addr);


    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) > 0 )
    {
        CUSTOM_ERROR("ERROR connecting");
        return -1;
    }
    CUSTOM_LOG("Connected to " << ip << ":"<< port);
    
    char buffer[22];
    while(1){
        int n = read(sockfd, buffer, sizeof(buffer));
        if (n < 0)
        {
            CUSTOM_ERROR("ERROR reading from socket");
            return -1;
        }
        if(n > 0){
            CUSTOM_LOG(buffer);
        }
    }

    return sockfd;
}