#include "lib/Serial.h" 
#include <iostream>
using namespace std;
int main(){

	Serial *s=new Serial();

    //example to scan all Serial ports on linux machine
	// vector<std::string> ports=s->scanPorts();
	// for(std::string s:ports)
	// 	cout<<s<<endl;
	

    // //example to open a definite Serial port and perform handshake
	// if(s->begin("/dev/ttyUSB0",B2000000)){
	// 	cout<<"\n  ttyUSB0 Opened Successfully\n";
    //     if(!s->handshake("handshake text"))
	// 		cout<<"\n No Device detected\n";
	//     else
    //         cout<<"\n"<<" handshake successful\n";
    //     //s->end();
    // }else
	// 	cout<<"\n  Error! in Opening ttyUSB0\n";



	//Search and connect to any device with the given handshake string at given 
	std::string responce = s->autoConnect("handshake text",B2000000);
    cout<<responce<<endl;
    for(int i=0;i<4;i++){
    int len=10;
    char handshake[len];
	memset(handshake,'\x00',(len+1)*sizeof(char));
    s->println("helloworld");
	int bytesRead = s->readBytes(&handshake,len);
    cout<<bytesRead<<endl;
    cout<<handshake<<endl;
    }
	cout<<"\nClosed\n";
    s->flushIO();
	s->end();



	return 0;
}
