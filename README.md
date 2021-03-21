# Serial-linux
A C++ Serial communication library that make easier to access Serial ports on linux device 



# Handshake
after opening a serial COM port the driver listens for response from the device if the responce matches the required handshake text we say a successful handshake is performed

Example for Microcontroller side code on Arduino boards for Handshake
```C++
void setup() {
 Serial.begin(2e6);
 Serial.println("handshake text");
}
```
# Run example code
To test this example sketch on you device make sure you have a Serial Device connected to device 
to test the handshake part make sure and auto connect feature make sure you have flashed microcontroller with the hanshake code
```
git clone https://github.com/Sayansree/Serial-linux.git
cd build 
cmake ..
make
./serialTest
```
To customise the example code edit example.cpp and rebuild the executable using make again
