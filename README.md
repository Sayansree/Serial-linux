# Serial-linux
A C++ Serial communication library that make easier to access Serial ports on linux device.
to use this library copy the `Serial.h` and `Serial.cpp` headers to you `include` directory

Functions available
<table>
  <tr>
    <th>return type</th>
    <th>function name</th>
    <th>function use</th>
  </tr>
  <tr>
    <td> </td>
    <td>Serial::Serial()</td>
    <td>Constructor</td>
  </tr>
  <tr>
    <td>bool</td>
    <td>Serial::begin(std::string, speed_t)</td>
    <td>opens a COM port with given name(string) and baudrate</td>
  </tr>
 <tr>
    <td>void</td>
    <td>Serial::end()</td>
    <td>closes current COM port</td>
  </tr>
 <tr>
    <td>void</td>
    <td>Serial::flushI()</td>
    <td>flushes Input buffer</td>
  </tr>
 <tr>
    <td>void</td>
    <td>Serial::flushO()</td>
    <td>flushes Input buffer</td>
  </tr>
 <tr>
    <td>void</td>
    <td>Serial::flushIO()</td>
    <td>flushes Input/Output buffer</td>
  </tr>
 <tr>
    <td>std::string</td>
    <td>Serial::autoConnect(std::string, speed_t)</td>
    <td>searches and connects with a device with 
     given handshake text(string) at given baudrate.
     returns empty string if none is found
     else the name of the port.
    </td>
  </tr>
 <tr>
    <td>std::vector&ltstd::string&gt</td>
    <td>Serial::scanPorts()</td>
    <td>returns List of all ttyACM and ttyUSB ports on device</td>
  </tr>
  <tr>
    <td>bool</td>
    <td>Serial:handshake(std::string)</td>
    <td>returns true if device handshakes successfully on the currently opened port</td>
  </tr>
  <tr>
    <td>void</td>
    <td>Serial:setReadTimeout(float)</td>
    <td>sets read timeout</td>
  </tr>
  <tr>
  <tr>
    <td>void</td>
    <td>Serial:setMinReadCharacter(uint8_t)</td>
    <td>sets minimum read character</td>
  </tr>
  <tr>
    <td>void</td>
    <td>Serial:print(std::string)</td>
    <td>write string on port</td>
  </tr>
  <tr>
    <td>void</td>
    <td>Serial:println(std::string)</td>
    <td>write string with new line on port</td>
  </tr>
  <tr>
    <td>ssize_t</td>
    <td>Serial:writeBytes(void*, size_t)</td>
    <td>write a byte array of given size to PORT</td>
  </tr>
  <tr>
    <td>ssize_t</td>
    <td>Serial:readBytes((void*, size_t)</td>
    <td>read a byte array of given size from PORT</td>
  </tr>
</table>

>>>>read write methords are under devlopment

## Scanning for available PORTs
Scanning all the Serial ports (ttyUSB and ttyACM) that are available on the device. scanPorts() returns a list of ports.

```C++
vector<string> ports=s->scanPorts();
for(string PORT:ports)
  cout<<PORT<<endl;
```


## Opening a PORT

```C++
Serial *port = new Serial();
port->begin("ttyUSB0", B9600);
```

## Closing a PORT

```C++
port->end();
```
## Handshake
after opening a serial COM port the driver listens for response from the device if the responce matches the required handshake text we say a successful handshake is performed

Example for Microcontroller side code on Arduino boards for Handshake
```C++
void setup() {
  Serial.begin(2e6);
  Serial.println("handshake text");
}
```
Example on device side for handshake
```C++
if(!port->handshake("handshake text"))
  cout<<"\n Handshake failed\n";
else
  cout<<"\n Handshake successful\n";
}
```
Note: before performing a handshake a port must be open

## Auto Connect
when the device supports a handshake, the driver can scan the device on all available ports, if it finds the device successfully it returns the port on which device is available or returns empty string if it cannot find the device.
Example of auto Connect.
```C++
string response = s->autoConnect("handshake text",B2000000);
if(response=="")
  cout<<"\n Device not found\n";
else
  cout<<"\n Device found on PORT "<<response<<"\n";
```

## Run example code

To test this example sketch on you device make sure you have a Serial Device connected to device 
to test the handshake part make sure and auto connect feature make sure you have flashed microcontroller with the hanshake code
```
git clone https://github.com/Sayansree/Serial-linux.git
cd Serial-linux
mkdir build
cd build
cmake ..
make
./serialTest
```
To customise the example code edit example.cpp and rebuild the executable using `make` again
