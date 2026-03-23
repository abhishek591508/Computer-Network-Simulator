#include "Hub.h"

Hub::Hub(string id) : Device(id) {}

void Hub::receive(const string& data, Device* sender) {

    cout << "[Hub " << id << "] Received data from ["
         << sender->getId() << "] -> Broadcasting...\n";

    for (auto device : connections) {

        // do not send back to sender
        if (device != sender) {
            device->receive(data, this);
        }

    }
}

