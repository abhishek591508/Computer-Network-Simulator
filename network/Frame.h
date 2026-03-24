#ifndef FRAME_H
#define FRAME_H

#include <string>

using namespace std;

class Frame {

public:

    string sourceMAC;
    string destinationMAC;
    string payload;
    int parityBit;
    

    Frame(string src, string dest, string data)
    {
        sourceMAC = src;
        destinationMAC = dest;
        payload = data;

        // compute parity for error detection
        int ones = 0;
        for(char c : payload) {
            if(c == '1') ones++;
        }
        parityBit = ones % 2;  // even parity
    }

};

#endif