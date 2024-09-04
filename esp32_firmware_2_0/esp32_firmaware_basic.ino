#include <string>

HardwareSerial lidar(1);

uint8_t read_byte;

void setup(){
  Serial.begin(115200);
  lidar.begin(115200, SERIAL_8N1, 18, 19);
}

void loop() {
  if(lidar.available()){
    while(lidar.available()){
      
      read_byte = lidar.read();
      Serial.write(read_byte);
    }
  }
  
}
