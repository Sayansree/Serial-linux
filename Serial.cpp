#include "Serial.h"


Serial::Serial(){
	fd=-1;
}
Serial::~Serial(){
	end();
}

bool Serial::begin(std::string port,speed_t BAUDRATE){
	if(PORT==port)return true;//to do check if disconnected
	if(fd>-1) end();
	fd = open(port.c_str(),O_RDWR | O_NOCTTY);
	if(fd ==-1)return false;
	tcgetattr(fd, &SerialPortSettings);
	cfsetspeed(&SerialPortSettings,BAUDRATE);
	SerialPortSettings.c_cflag &= ~(PARENB|CSTOPB|CSIZE|CRTSCTS);   // No Parity,stop bits 1, clear data bit mask,Turn off hardware based flow control (RTS/CTS).
	SerialPortSettings.c_cflag |=  CS8|CREAD|CLOCAL;   //Set the data bits = 8 , turn on receiver
	SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY | INLCR | ICRNL | IGNCR);
	SerialPortSettings.c_oflag &= ~(ONLCR | OCRNL);
	SerialPortSettings.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHONL | ISIG | IEXTEN);
	SerialPortSettings.c_cc[VMIN]  = 1; /* Read 10 characters */
	SerialPortSettings.c_cc[VTIME] = 1; //timout 100ms (value=timeout in sec*10)
	tcsetattr(fd,TCSANOW,&SerialPortSettings);
	PORT=port;
	return true;
}
void Serial::end(){
	if(fd=-1)return;
	close(fd);
	fd=-1;
	PORT="";
}
void Serial::flushI(){
	tcflush(fd,TCIFLUSH);
}
void Serial::flushO(){
	tcflush(fd,TCOFLUSH);
}
void Serial::flushIO(){
	tcflush(fd,TCIOFLUSH);
}
void Serial::setReadTimeout(float sec){
	SerialPortSettings.c_cc[VTIME] = (uint8_t)(sec*10);
	tcsetattr(fd,TCSANOW,&SerialPortSettings);
}
void Serial::setMinReadCharacter(uint8_t size){
	SerialPortSettings.c_cc[VTIME] = size;
	tcsetattr(fd,TCSANOW,&SerialPortSettings);
}
std::string Serial::autoConnect(std::string HANDSHAKE_REF,speed_t BAUDRATE){
	std::vector<std::string> ports=scanPorts();
	for(std::string port:ports){
		begin(port,BAUDRATE);
		if(handshake(HANDSHAKE_REF)){
			PORT=port;
			return port;
		}else
			end();
	}
	PORT="";
	return "";
}
bool Serial::handshake(std::string HANDSHAKE_REF){
	if(fd==-1)return false;
	int  bytesRead = 0,len = HANDSHAKE_REF.length();
	char handshake[len];
	memset(handshake,'\x00',(len+1)*sizeof(char));
	SerialPortSettings.c_cc[VMIN]  = len; /* Read 10 characters */
	SerialPortSettings.c_cc[VTIME] = 25; //timout 2.5s (value=timeout in sec*10)
	tcsetattr(fd,TCSANOW,&SerialPortSettings);
	bytesRead = readBytes(&handshake,len);
	std::cout << bytesRead << '\n';
	return bytesRead == len && strcmp(HANDSHAKE_REF.c_str(),handshake) == 0;
}
ssize_t Serial::readBytes(void* buf,size_t bytes){
	return read(fd,buf,bytes);
}
ssize_t Serial::readBytesUntil(unsigned char eol, void * buf,size_t bytes){

}
std::string Serial::readLine(){

}
ssize_t Serial::writeBytes(void* buf,size_t bytes){
	return write(fd,buf,bytes);
}
bool Serial::print(std::string str){
	writeBytes(&str[0],str.length());
}
bool Serial::println(std::string str){
	str+="\n";
	print(str);
}
std::string Serial::exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}
std::vector <std::string> Serial::scanPorts(){
		std::vector <std::string> portsACM,portsUSB,ports;
		std::string result= exec("ls /dev/ttyACM[0-9]\n");
		if(result!=""){
			boost::split(portsACM,result,boost::is_any_of("\n"));
			portsACM.pop_back();
		}
		result= exec("ls /dev/ttyUSB[0-9]\n");
		if(result!=""){
			boost::split(portsUSB,result,boost::is_any_of("\n"));
			portsUSB.pop_back();
		}
		ports.insert(ports.begin(),portsACM.begin(),portsACM.end());
		ports.insert(ports.begin(),portsUSB.begin(),portsUSB.end());
		return ports;
}

