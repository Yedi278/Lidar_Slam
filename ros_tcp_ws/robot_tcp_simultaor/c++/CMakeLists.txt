cmake_minimum_required(VERSION 3.0.2)
project(TCP_Test)


add_executable(TCP_Test main.cpp tcp_receive.cpp tcp_receive.h)
target_link_libraries(TCP_Test ${catkin_LIBRARIES})