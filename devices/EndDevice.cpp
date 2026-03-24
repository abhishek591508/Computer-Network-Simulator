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

// Commented above code in step 4
#include "EndDevice.h"

EndDevice::EndDevice(string id, string mac) : Device(id)
{
    macAddress = mac;
}

string EndDevice::getMAC()
{
    return macAddress;
}

void EndDevice::send(string data, string destMAC)
{

    // Create a frame
    Frame frame(macAddress, destMAC, data);

    cout << "[" << id << "] sending frame\n";
    cout << "SRC=" << frame.sourceMAC
         << " DEST=" << frame.destinationMAC
         << " DATA=" << frame.payload << endl;

    // send frame to connected devices
    for (auto device : connections)
    {
        device->receive(frame, this);
    }
}



void EndDevice::receive(Frame frame, Device* sender) {

    // Step 1: Check if frame is intended for this device
    if (frame.destinationMAC != macAddress) {
        cout << "[" << id << "] Silently ignoring frame\n";
        return;
    }

    cout << "[" << id << "] received frame from "
         << sender->getId() << endl;

    // Step 2: Recalculate parity
    int ones = 0;

    for(char c : frame.payload) {
        if(c == '1') ones++;
    }

    int computedParity = ones % 2;

    // Step 3: Compare parity
    if(computedParity != frame.parityBit) {

        cout << "[ERROR] Frame corrupted during transmission\n";
        return;

    }

    cout << "[SUCCESS] Frame received correctly\n";
    cout << "Payload: " << frame.payload << endl;

}
