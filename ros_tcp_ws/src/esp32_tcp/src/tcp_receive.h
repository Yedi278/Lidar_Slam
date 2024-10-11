#ifndef TCP_RECEIVE_H
#define TCP_RECEIVE_H

#include <thread>
#include "ros/ros.h"
#include "ros/console.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int connect_tcp(const char *ip, int port);

#endif // TCP_RECEIVE_H