/* written by Sayansree Paria
    email : sayansreeparia@gmail.com
    github : https://github.com/Sayansree
    linklin : https://www.linkedin.com/in/sayansreeparia
*/

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
  void setReadTimeout(float);
  void setMinReadCharacter(uint8_t);
  ssize_t readBytes(void*, size_t);
  bool print(std::string);
  bool println(std::string);
  ssize_t writeBytes(void*, size_t);
  ssize_t readBytesUntil(unsigned char, void*, size_t);
  std::string readLine(size_t maxSize=255);
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
