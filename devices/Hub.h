#ifndef HUB_H
#define HUB_H

#include "Device.h"

class Hub : public Device {
public:
    Hub(string id);

    // hub receives and broadcasts
    void receive(const string& data, Device* sender) override;
};

#endif