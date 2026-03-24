// #include "EndDevice.h"

// EndDevice::EndDevice(string id) : Device(id) {}

// void EndDevice::send(const string& data, Device* destination) {
//     cout << "[" << id << "] Sending data to [" 
//          << destination->getId() << "]: " << data << endl;

//     // send only to directly connected device (for now)
//     for (auto device : connections) {
//         if (device == destination) {
//             device->receive(data, this);
//             return;
//         }
//     }

//     cout << "[" << id << "] can not send the data to "<<"["<<destination->getId()<<"] because they are not directly connected.";
// }

// void EndDevice::receive(const string& data, Device* sender) {
//     cout << "[" << id << "] Received data from [" 
//          << sender->getId() << "]: " << data << endl;
// }



//Commented above code in step 4
#include "EndDevice.h"

EndDevice::EndDevice(string id, string mac) : Device(id) {
    macAddress = mac;
}

string EndDevice::getMAC() {
    return macAddress;
}

void EndDevice::send(string data, string destMAC) {

    // Create a frame
    Frame frame(macAddress, destMAC, data);

    cout << "[" << id << "] sending frame\n";
    cout << "SRC=" << frame.sourceMAC
         << " DEST=" << frame.destinationMAC
         << " DATA=" << frame.payload << endl;

    // send frame to connected devices
    for (auto device : connections) {
        device->receive(frame, this);
    }

}

void EndDevice::receive(Frame frame, Device* sender) {

    // accept only if MAC matches
    if (frame.destinationMAC == macAddress) {

        cout << "[" << id << "] received frame from ["
             << sender->getId() << "]\n";

        cout << "Payload: " << frame.payload << endl;
    }
    else {
        cout << "[" << id << "] Silently ignoring frame\n";
    }

}