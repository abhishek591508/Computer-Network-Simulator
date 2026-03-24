Important Design Choices (very important for future steps)

for compiling :
```
g++ main.cpp devices/Device.cpp devices/EndDevice.cpp devices/Hub.cpp
```
for running :
```
./a 
```



```
network_simulator/
│
├── main.cpp
│
├── devices/
│   ├── Device.h
│   ├── Device.cpp
│   ├── EndDevice.h
│   ├── EndDevice.cpp
│   ├── Hub.h
│   └── Hub.cpp
│
└── network/
    ├── Frame.h
    └── Frame.cpp      
```

step-1
isme hmne device.cpp & device.h build kiye & fir main.cpp me testing kr li.Right now your base Device is doing blind broadcasting (sending to all connections).That’s not realistic. In real networks:
we'll improve it in next step-2.



step-2
isme hmne endDevice.h & endDevice.cpp bnaya, isme device can send data to specific device & can detect invalid path


step-3
isme hamne hub.cpp and hub.h banaya.
You now have a working Physical Layer Simulation supporting:
End devices
Hub
Star topology
Broadcast transmission
This satisfies part of the assignment requirement:
Create a star topology with five end devices connected to a hub and enable communication.



step-4(we did it in 4 parts 4.1 4.2 4.3 and 4.4)
Here we start the work of Data link layer, Frame.h bnaya.
isme hmne framing(srcMAC,destMAC,data) introduce kiya, sbhi devices(endDevice,hub) jo data ke sath kam kr rhe the unhe frame se replace kiya.



step-5
here we create switch.h & switch.cpp
implement macTable display, macAddress learning, performing flooding for the first time and then Unicast forwarding then after.