Important Design Choices (very important for future steps)

network_simulator/
│
├── main.cpp
│
├── devices/
│   ├── Device.h
│   └── Device.cpp
│
└── utils/        (keep for future use, optional for now)


step-1
isme hmne device.cpp & device.h build kiye & fir main.cpp me testing kr li.Right now your base Device is doing blind broadcasting (sending to all connections).That’s not realistic. In real networks:
we'll improve it in next step-2.

To run: g++ main.cpp devices/Device.cpp devices/EndDevice.cpp & ./a.exe

