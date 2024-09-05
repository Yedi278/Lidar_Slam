#include <iostream>
#define PACKET_SIZE 22

struct single_packet{
  int angle;
  int distance;
  int signal_strength;
};

class Packet
{
private:
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

  single_packet get_packets(int i){

    single_packet sp;
    sp.angle = angle[i];
    sp.distance = distance[i];
    sp.signal_strength = signal_strength[i];
    
    return sp;
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