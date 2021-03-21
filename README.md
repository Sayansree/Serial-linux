# Serial-linux
A C++ Serial communication library that make easier to access Serial ports on linux machine 


```
git clone https://github.com/Sayansree/Serial-linux.git
cd build 
cmake ..
make
./serialTest
```
# Handshake
example for Microcontroller side code on Arduino boards for Handshake
```C++
void setup() {
 Serial.begin(2e6);
 Serial.println("handshake text");
}
```
