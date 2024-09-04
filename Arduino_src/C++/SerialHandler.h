#include <string>
#include <iostream>
#include "Packet.h"

class SerialHandler
{
private:
  /// Serial port path
  std::string port;

  /// File descriptor for the serial port
  int tty_fd;

public:
  SerialHandler(std::string port);
  
  void init_serial_port();

  Packet read_data_packet();

  ~SerialHandler();
};