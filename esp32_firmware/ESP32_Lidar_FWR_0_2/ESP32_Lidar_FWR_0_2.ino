/**
 * @file ESP32_Lidar_FWD.ino Arduino file
 * @details Firmware for Esp32-S3 UNO.
 * This software is designed to receive the lidar UART transmission at 115200 baud rate.
 * The signal is processed and sent back to Serial transmission at the PC at 115200 baud rate.
 * @author Yehan Edirisinghe yehan278@gmail.com
 * 
 */
#include <HardwareSerial.h>
#include <vector>

// specifications for UART data trasmission
#define RXPIN 19
#define TXPIN 18
#define BAUDRATE 115200 //transmission speed

// using UART1
HardwareSerial Lidar(1);

// data acquisition variables
uint8_t read_byte;
uint8_t read_byte_old;

// data input buffer
std::vector<unsigned char> data_buffer;

typedef std::vector<unsigned char>::const_iterator buffer_pointer;

bool is_dist_valid(buffer_pointer it){
  return (*std::next(it,1) & 0x80) >> 7;
}

/**
 * @brief This function calculates the distance given the pointer to the distance bytes
 * @details The function requires the iterator to be at the point of the first byte.
 * It only calculates one distance.
 * @param buffer_pointer it iterator to the start byte
 * @return int distance in millimiters
 */
int dist(buffer_pointer it){
  //if(is_dist_valid(it) == false) return -1;
  return *it | (( *std::next(it,1) & 0x3F) << 8);
}

/**
 * @brief 
 */
void process(buffer_pointer it){
  //4 data packets

  int angle = *std::next(it,1) - 0xa0;
  float rpm = float(*std::next(it,2) | ((*std::next(it,3)<<8))) / 64.f;

  for(int i=0; i<4; i++){
    // Serial.println("angle: "+String(4*angle+i)+"\trpm: "+String(rpm)+"\tdist: "+String(dist(std::next(it,4+4*i))));
    String a = String(4*angle+i)+","+String(rpm)+","+String(dist(std::next(it,4+4*i)))+"\n";
    Serial.write(a.c_str());

  }
}

void print(const std::vector<unsigned char> &data_buffer){

  // Serial.println();
  // Serial.println("NEW DATA PACKET");
  // Serial.println("data packet size: "+String(data_buffer.size()));

  buffer_pointer it;
  for(it=data_buffer.begin(); it!=data_buffer.end(); it++){

    if(*it == 0xfa && *(std::next(it,1)) <= 0xf9 && *(std::next(it,1)) >= 0xa0 ){

      // buffer_pointer jt;
      // for(jt=it; jt!=std::next(it,22); jt++){
      //   Serial.print(*jt, HEX);
      // }
      // Serial.println();

      process(it);
    }
  }
}

void setup()
{
  // initialise serial comunication
  Serial.begin(BAUDRATE);

  // ensure TXPIN is only for receiving data
  pinMode(TXPIN, INPUT);
  Lidar.begin(BAUDRATE, SERIAL_8N1, RXPIN, TXPIN);
}

void loop() {
  
  if(Lidar.available()){
    while(Lidar.available()){
      
      read_byte = Lidar.read();
      if(read_byte != -1){
        
        if(read_byte_old == 0xfa && read_byte == 0xa0 ){

          data_buffer.pop_back(); // remove last 0xFA
          
          print(data_buffer);

          data_buffer.clear();

          data_buffer.push_back(0xfa); //re-add last 0xFA
        }

        data_buffer.push_back(read_byte);
        read_byte_old = read_byte;
      }
    }
  }
}