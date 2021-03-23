#ifndef SERIAL_H
#define SERIAL_H

#include <iostream>
#include <string>
#include <fcntl.h>  /* File Control Definitions          */
#include <termios.h>/* POSIX Terminal Control Definitions*/
#include <vector>
#include <boost/algorithm/string.hpp>

class Serial{

public:
  Serial();
  ~Serial();
  bool begin(std::string, speed_t);
  void end();
  void flushI();
  void flushO();
  void flushIO();
  void setReadTimeout(float sec);
  void setMinReadCharacter(uint8_t size);
  ssize_t readBytes(void*, size_t);
  ssize_t writeBytes(void*, size_t);
  bool print(std::string);
  bool println(std::string);
  std::string readLine();
  std::string autoConnect(std::string, speed_t);
  std::vector <std::string> scanPorts();
  bool handshake(std::string);

private:
  std::string exec(const char*);
  std::string PORT;
  termios SerialPortSettings;
  int fd;
};

#endif
