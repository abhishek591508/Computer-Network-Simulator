#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Device {
protected:
    string id;
    vector<Device*> connections;   // stores connected devices

public:
    Device(string id);

    string getId() const;

    // connect this device to another
    void connect(Device* device);

    // virtual functions (will be overridden later)
    virtual void send(const string& data);
    virtual void receive(const string& data, Device* sender);

    // helper to print connections (for testing)
    void showConnections() const;

    virtual ~Device() {}
};

#endif