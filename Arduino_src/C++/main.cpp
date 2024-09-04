#include "SerialHandler.h"

int main(int argc, char **argv) {

  SerialHandler sh("/dev/ttyUSB0");

  Packet p;
  while(1){

    p = sh.read_data_packet();
    if(p._is_valid()){
      p.extrapolate();
      // std::cout << static_cast<int>(p.angle[0] - 0xa0) << std::endl;
      for(int i=0; i<4; i++){
        std::cout << "Angle: " << p.angle[i] << " Distance: " << p.distance[i] << " Signal Strenght: " << p.signal_strength[i] << std::endl;
      }
    }
  }

  return 0;
}