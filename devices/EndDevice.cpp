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
#include "../network/Channel.h"
#include "../network/AckBuffer.h"
#include <cstdlib>
#include <windows.h>
#include <iostream>
using namespace std;
// These are needed for: random delay & simulated waiting

EndDevice::EndDevice(string id, string mac) : Device(id)
{
    macAddress = mac;
    nextSeq = 0;
    base = 0;
    windowSize = 3;
}

string EndDevice::getMAC()
{
    return macAddress;
}

// void EndDevice::send(string data, string destMAC)
// {

//     // Create a frame
//     Frame frame(macAddress, destMAC, data);

//     cout << "[" << id << "] sending frame\n";
//     cout << "SRC=" << frame.sourceMAC
//          << " DEST=" << frame.destinationMAC
//          << " DATA=" << frame.payload << endl;

//     // send frame to connected devices
//     for (auto device : connections)
//     {
//         device->receive(frame, this);
//     }
// }

// update it in step-7 for carrier sensing and collision detection
void EndDevice::send(string data, string destMAC)
{

    int attempts = 0;

    while (attempts < 3)
    {

        // Sliding Window Check
        if (nextSeq >= base + windowSize)
        {
            cout << "[" << id << "] window full, waiting for ACK\n";
            return;
        }

        // Carrier Sense
        if (Channel::busy)
        {
            cout << "[" << id << "] channel busy, waiting...\n";
            return;
        }
        Channel::busy = true;

        Frame frame(macAddress, destMAC, data, nextSeq);

        cout << "[" << id << "] sending frame\n";
        cout << "SEQ=" << frame.sequenceNumber
             << " SRC=" << frame.sourceMAC
             << " DEST=" << frame.destinationMAC
             << " DATA=" << frame.payload << endl;

        nextSeq++;

        // simulate collision condition
        if (Channel::collision)
        {

            cout << "[" << id << "] collision detected\n";
            Channel::busy = false;
            // Channel::collision = false; // reset collision for next attempt

            // random backoff
            int delay = rand() % 3 + 1;
            cout << "[" << id << "] backing off for "
                 << delay << " seconds\n";

            Sleep(delay * 1000);

            attempts++;
            continue;
        }
        // normal transmission
        for (auto device : connections)
        {
            device->receive(frame, this);
        }
        Channel::busy = false;
        return;
    }
    cout << "[" << id << "] transmission failed after retries\n";
}

void EndDevice::receive(Frame frame, Device *sender)
{

    // ignore frames not meant for this device
    if (frame.destinationMAC != macAddress)
    {
        cout << "[" << id << "] Silently ignoring frame\n";
        return;
    }

    // handle ACK frames
    if (frame.isACK)
    {

        cout << "[" << id << "] received ACK for SEQ="
             << frame.sequenceNumber << endl;

        base = frame.sequenceNumber + 1;

        cout << "[" << id << "] window slides, new base = "
             << base << endl;

        return;
    }

    cout << "[" << id << "] received frame SEQ="
         << frame.sequenceNumber << " from "
         << sender->getId() << endl;

    // parity check
    int ones = 0;

    for (char c : frame.payload)
    {
        if (c == '1')
            ones++;
    }

    int computedParity = ones % 2;

    if (computedParity != frame.parityBit)
    {

        cout << "[ERROR] Frame corrupted during transmission\n";
        return;
    }

    cout << "[SUCCESS] Frame received correctly\n";
    cout << "Payload: " << frame.payload << endl;

    // create ACK
    // Frame ack(macAddress, frame.sourceMAC, "", frame.sequenceNumber, true);

    // cout << "[" << id << "] sending ACK "
    //      << frame.sequenceNumber << endl;

    // for(auto device : connections) {
    //     device->receive(ack, this);
    // }

    Frame ack(macAddress, frame.sourceMAC, "", frame.sequenceNumber, true);

    cout << "[" << id << "] generating ACK "
         << frame.sequenceNumber << endl;

    AckBuffer::buffer.push(ack);
}
