#ifndef ENDDEVICE_H
#define ENDDEVICE_H

#include "Device.h"

class EndDevice : public Device {
public:
    EndDevice(string id);

    // send to specific destination
    void send(const string& data, Device* destination);

    // override receive
    void receive(const string& data, Device* sender) override;
};

#endif