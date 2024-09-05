#include "SerialHandler.h"

int main(int argc, char **argv) {

  SerialHandler sh("/dev/ttyUSB0");

  Packet p;
  while(1){

    p = sh.read_data_packet();
    if(p._is_valid()){

      p.extrapolate();

      single_packet sp;

      for(int i=0; i<4; i++){
        sp = p.get_packets(i);
        std::cout << "Angle: " << sp.angle << " Distance: " << sp.distance << " Signal Strength: " << sp.signal_strength << std::endl;
      }

    }else{
      std::cout << "Invalid packet" << std::endl;
    }
  }

  return 0;
}