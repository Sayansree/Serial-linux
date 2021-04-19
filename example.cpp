#include "Serial.h" 
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
	std::string responce = s->autoConnect("handshake text\r\n",B2000000);
    cout<<responce<<endl;
    s->setMinReadCharacter(1);
    s->setReadTimeout(0.1);
    for(int i=0;i<4;i++){
        s->println("helloworld");
        // int len=15;
        // char handshake[len];
        // int bytesRead;
        //memset(handshake,'\x00',(len+1)*sizeof(char));
        //bytesRead = s->readBytes(&handshake,len);
        //bytesRead = s->readBytesUntil('\n',&handshake,len);
        //cout<<"read:"<<bytesRead<<"\t"<<handshake<<endl;
        cout<<s->readLine();
    }
	cout<<"\nClosed\n";
    s->flushIO();
	s->end();



	return 0;
}
