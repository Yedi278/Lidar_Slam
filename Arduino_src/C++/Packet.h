#include <iostream>
#define PACKET_SIZE 22

struct single_packet{
  int angle;
  int distance;
  int signal_strength;
};

class Packet
{
public:
  int angle[4];
  float rpm;
  int distance[4];
  int signal_strength[4];

public:
  const int packet_size = PACKET_SIZE;
  unsigned int data[PACKET_SIZE];

  Packet();
  
  bool _is_valid();

  void extrapolate();

  void print(){
    for(int i=0; i<22; i++){
      std::cout << std::hex << data[i] << " ";
    }
    std::cout << std::endl;
  }

  Packet& operator=(const Packet& p){
    for(int i=0; i<22; i++){
      data[i] = p.data[i];
    }
    extrapolate();
    return *this;
  }

  Packet(const Packet& p){
    for(int i=0; i<22; i++){
      data[i] = p.data[i];
    }
    extrapolate();
  }

  ~Packet();
};