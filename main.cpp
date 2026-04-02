#include "devices/EndDevice.h"
#include "devices/Hub.h"
#include "network/AckBuffer.h"
#include "network/Channel.h"
#include <iostream>

using namespace std;

void deliverACKs(Device *receiver)
{
    while (!AckBuffer::buffer.empty())
    {
        Frame ack = AckBuffer::buffer.front();
        AckBuffer::buffer.pop();
        receiver->receive(ack, receiver);
    }
}

void connectStar(EndDevice &A, EndDevice &B, Hub &H)
{
    A.connect(&H);
    H.connect(&A);
    B.connect(&H);
    H.connect(&B);
}

void demo_gbn()
{
    cout << "\n========== Go-Back-N (cumulative ACK) ==========\n\n";

    EndDevice A("A", "MAC_A", ReliableProtocol::GBN);
    EndDevice B("B", "MAC_B", ReliableProtocol::GBN);
    Hub H1("H1");
    connectStar(A, B, H1);

    Channel::busy = false;
    Channel::collision = false;

    A.send("101101", "MAC_B");
    A.send("111000", "MAC_B");
    A.send("110011", "MAC_B");
    A.send("100111", "MAC_B");

    cout << "\n--- Delivering ACKs (GBN: each ACK slides base by cumulative amount) ---\n\n";
    deliverACKs(&A);

    A.send("100111", "MAC_B");

    cout << "\n--- Second ACK batch ---\n\n";
    deliverACKs(&A);
}

void demo_sr()
{
    cout << "\n========== Selective Repeat (individual ACK) ==========\n\n";

    EndDevice A("A", "MAC_A", ReliableProtocol::SelectiveRepeat);
    EndDevice B("B", "MAC_B", ReliableProtocol::SelectiveRepeat);
    Hub H1("H1");
    connectStar(A, B, H1);

    Channel::busy = false;
    Channel::collision = false;

    A.send("101101", "MAC_B");
    A.send("111000", "MAC_B");
    A.send("110011", "MAC_B");
    A.send("100111", "MAC_B");

    cout << "\n--- Delivering ACKs (SR: each ACK marks one sequence number) ---\n\n";
    deliverACKs(&A);

    A.send("100111", "MAC_B");

    cout << "\n--- Second ACK batch ---\n\n";
    deliverACKs(&A);
}

int main()
{
    demo_gbn();
    demo_sr();
    return 0;
}
