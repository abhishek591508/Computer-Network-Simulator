#ifndef ENDDEVICE_H
#define ENDDEVICE_H

#include "Device.h"

enum class ReliableProtocol
{
    GBN,
    SelectiveRepeat
};

class EndDevice : public Device
{

private:
    string macAddress;
    ReliableProtocol protocol;
    int nextSeq;
    int base;
    int windowSize;

    // GBN receiver
    int expectedSeq;

    // Selective Repeat receiver
    int rcv_base;
    vector<bool> sr_recvFilled;
    vector<string> sr_recvPayload;

    // Selective Repeat sender: per-sequence ACK received
    vector<bool> sr_acked;

public:
    static const int SEQ_MOD = 8;

    EndDevice(string id, string mac,
              ReliableProtocol p = ReliableProtocol::GBN);

    string getMAC();

    ReliableProtocol getProtocol() const { return protocol; }

    void setProtocol(ReliableProtocol p);

    void setWindowSize(int w);

    void send(string data, string destMAC);

    void receive(Frame frame, Device *sender) override;
};

#endif
