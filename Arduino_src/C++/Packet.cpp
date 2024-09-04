#include "Packet.h"

Packet::Packet(){
  for(int i=0; i<22; i++){
    data[i] = 0;
  }
}

Packet::~Packet(){
}

bool Packet::_is_valid(){
  return data[0] == 0xfa && data[1] >= 0xa0 && data[1] <= 0xf9;
}

void Packet::extrapolate(){
  
  if (!_is_valid()) return;
  rpm = float(data[2] | ((data[3]<<8))) / 64.f;

  for(int i=0; i<4; i++){
    angle[i] = static_cast<int>(data[1] - 0xa0)*4 + i;
    distance[i] = data[4+i*4] | (( data[5+i*4] & 0x3F) << 8);
    signal_strength[i] = data[6+i*4] | (data[7+i*4] << 8);
  }
}