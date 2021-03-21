#include "lib/Serial.h" 
#include <iostream>
using namespace std;
int main(){

	Serial *s=new Serial();

    //example to scan all Serial ports on linux machine
	vector<std::string> ports=s->scanPorts();
	for(std::string s:ports)
		cout<<s<<endl;
	

    //example to open a definite Serial port and perform handshake
	if(s->begin("/dev/ttyUSB0",B2000000)){
		cout<<"\n  ttyUSB0 Opened Successfully\n";
        if(!s->handshake("Quantum Ground Station"))
			cout<<"\n No Device detected\n";
	    else
            cout<<"\n"<<" handshake successful\n";
        s->end();
    }else
		cout<<"\n  Error! in Opening ttyUSB0\n";



	//Search and connect to any device with the given handshake string at given 
	std::string responce = s->autoConnect("handshake text",B2000000);
	cout<<"\n  ttyUSB0 Closed\n";
	s->end();


    
	return 0;
}
