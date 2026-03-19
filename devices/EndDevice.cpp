#include "EndDevice.h"

EndDevice::EndDevice(string id) : Device(id) {}

void EndDevice::send(const string& data, Device* destination) {
    cout << "[" << id << "] Sending data to [" 
         << destination->getId() << "]: " << data << endl;

    // send only to directly connected device (for now)
    for (auto device : connections) {
        if (device == destination) {
            device->receive(data, this);
            return;
        }
    }

    cout << "[" << id << "] Destination not directly connected.\n";
}

void EndDevice::receive(const string& data, Device* sender) {
    cout << "[" << id << "] Received data from [" 
         << sender->getId() << "]: " << data << endl;
}