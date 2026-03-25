// #ifndef ENDDEVICE_H
// #define ENDDEVICE_H

// #include "Device.h"

// class EndDevice : public Device {
// public:
//     EndDevice(string id);

//     // send to specific destination
//     void send(const string& data, Device* destination);

//     // override receive
//     void receive(const string& data, Device* sender) override;
// };

// #endif



//Commented above code in step 4
#ifndef ENDDEVICE_H
#define ENDDEVICE_H

#include "Device.h"

class EndDevice : public Device {

private:
    string macAddress;
    int nextSeq;
    int base;         // start of window
    int windowSize;   // window size

public:
    EndDevice(string id, string mac);

    string getMAC();

    // send now uses destination MAC
    void send(string data, string destMAC);

    // UPDATED receive
    void receive(Frame frame, Device* sender) override;

};

#endif