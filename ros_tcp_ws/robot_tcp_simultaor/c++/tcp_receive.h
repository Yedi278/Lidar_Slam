#ifndef TCP_RECEIVE_H
#define TCP_RECEIVE_H

#include <thread>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

#define CUSTOM_LOG(x) std::cout << x << std::endl
#define CUSTOM_ERROR(x) std::cerr << x << std::endl

/**
 * @brief Connect to a TCP server
 */
int connect_tcp(const char *ip, int port);

#endif // TCP_RECEIVE_H