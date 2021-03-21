#include "lib/Serial.h" 
#include <iostream>
using namespace std;
int main(){

	Serial *s=new Serial();
	// vector<std::string> ports=s->scanPorts();
	// for(std::string s:ports)
	// 	cout<<s<<endl;
	// std::string responce = s->autoConnect("Quantum Ground Station",B2000000);
	if(s->begin("/dev/ttyUSB0",B2000000)){
		cout<<"\n  ttyUSB0 Opened Successfully\n";
        if(!s->handshake("Quantum Ground Station"))
			cout<<"\n No Device detected\n";
	    else
            cout<<"\n"<<" handshake successful\n";
            vector<std::string> ports=s->scanPorts();
            for(std::string s:ports)
                cout<<s<<endl;
    }else
		cout<<"\n  Error! in Opening ttyUSB0\n";
	
	std::string responce = s->autoConnect("Quantum Ground Station",B2000000);
	cout<<"\n  ttyUSB0 Closed\n";
	s->end();
	return 0;
}
