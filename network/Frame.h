#ifndef FRAME_H
#define FRAME_H

#include <string>

using namespace std;

class Frame {

public:

    string sourceMAC;
    string destinationMAC;
    string payload;

    Frame(string src, string dest, string data)
    {
        sourceMAC = src;
        destinationMAC = dest;
        payload = data;
    }

};

#endif