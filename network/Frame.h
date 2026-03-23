#ifndef FRAME_H
#define FRAME_H

#include <string>

using namespace std;

class Frame {
public:
    string srcMAC;
    string destMAC;
    string payload;

    Frame(string src, string dest, string data);
};

#endif