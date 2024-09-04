#include "SerialHandler.h"
#include <termios.h>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>

SerialHandler::SerialHandler(std::string port)
{
  this->port = port;
  this->tty_fd = open(this->port.c_str(), O_RDWR);
  if (this->tty_fd < 0) {
      std::cerr << "Could not open port " << this->port << std::endl;
  }else{
    std::cerr << "Opened serial port " << this->port << std::endl;
  }
  init_serial_port();
}

void SerialHandler::init_serial_port(){

  struct termios tty_opt;
  memset(&tty_opt, 0, sizeof(tty_opt));
  tty_opt.c_cflag = CS8 | CLOCAL | CREAD; // CS8: 8n1, CLOCAL: local connection, no modem contol, CREAD: enable receiving characters
  tty_opt.c_iflag = 0;
  tty_opt.c_oflag = 0;
  tty_opt.c_lflag = 0;     // non-canonical mode
  tty_opt.c_cc[VMIN] = 1;  // blocking read until 1 character arrives
  tty_opt.c_cc[VTIME] = 0; // inter-character timer unused
  cfsetospeed(&tty_opt, B115200);
  cfsetispeed(&tty_opt, B115200);

  tcsetattr(this->tty_fd, TCSANOW, &tty_opt);
}

Packet SerialHandler::read_data_packet(){
  Packet p;

  if(1==read(this->tty_fd,p.data,1)   && 0xfa == p.data[0] &&
     1==read(this->tty_fd,p.data+1,1) && p.data[1] >= 0xa0 
                                      && p.data[1] <= 0xf9){

    int count=2;
    while(count<22){
      if(1==read(this->tty_fd,(p.data+count),1))
        count++;
    }
  }
  return p;
}

SerialHandler::~SerialHandler(){
  close(this->tty_fd);
}