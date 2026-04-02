
//step 1
// #include "devices/Device.h"

// int main() {
//     // create devices
//     Device A("A");
//     Device B("B");

//     // connect A <-> B
//     A.connect(&B);
//     B.connect(&A);

//     // verify connections
//     A.showConnections();
//     B.showConnections();

//     // simple send test
//     A.send("Hello B");

//     return 0;
// }




//Step-2
// #include "devices/EndDevice.h"
// int main() {
//     EndDevice A("A");
//     EndDevice B("B");
//     EndDevice C("C");

//     // connections
//     A.connect(&B);
//     B.connect(&A);

//     B.connect(&C);
//     C.connect(&B);

//     // test direct communication
//     A.send("Hello B", &B);

//     // test non-direct
//     A.send("Hello C", &C);

//     return 0;
// }




//step 3 
//Create a star topology with five end devices connected to a hub and enable communication.
// #include "devices/EndDevice.h"
// #include "devices/Hub.h"

// int main() {

//     EndDevice A("A");
//     EndDevice B("B");
//     EndDevice C("C");
//     EndDevice D("D");

//     Hub hub("H1");

//     // connect devices to hub
//     A.connect(&hub);
//     hub.connect(&A);

//     B.connect(&hub);
//     hub.connect(&B);

//     C.connect(&hub);
//     hub.connect(&C);

//     D.connect(&hub);
//     hub.connect(&D);

//     cout << "\n--- Star Topology Test ---\n\n";

//     A.send("Hello Everyone", &hub);

//     return 0;
// }




//step 4
// #include "devices/EndDevice.h"
// #include "devices/Hub.h"
// #include "devices/Switch.h"

// int main() {

//     EndDevice A("A", "MAC_A");
//     EndDevice B("B", "MAC_B");
//     EndDevice C("C", "MAC_C");

//     Hub hub("H1");

//     A.connect(&hub);
//     hub.connect(&A);

//     B.connect(&hub);
//     hub.connect(&B);

//     C.connect(&hub);
//     hub.connect(&C);

//     cout << "\n--- Frame Transmission Test ---\n\n";

//     A.send("Hello B", "MAC_B");

// }




//step 5 will be to implement a simple CLI to allow users to create devices, connect them, and send messages interactively.
// #include "devices/EndDevice.h"
// #include "devices/Hub.h"
// #include "devices/Switch.h"

// int main() {

//     EndDevice A("A", "MAC_A");
//     EndDevice B("B", "MAC_B");
//     EndDevice C("C", "MAC_C");


//     Switch switch1("S1");
//     switch1.connect(&A);
//     switch1.connect(&B);
//     switch1.connect(&C);
//     A.connect(&switch1);
//     B.connect(&switch1);
//     C.connect(&switch1);


//     //send frame through switch
//     A.send("Hello B through Switch", "MAC_B");
//     //b ko known hona chahiye ki A ne message bheja hai
//     B.send("Hello A through Switch", "MAC_A");

//     switch1.printMACTable();
// }



//step 6 will be to implement error detection using parity bits in the frame structure and simulate error scenarios.
// #include "devices/EndDevice.h"
// #include "devices/Hub.h"
// #include "devices/Switch.h"

// int main() {

//     EndDevice A("A", "MAC_A");
//     EndDevice B("B", "MAC_B");
//     Hub hub("H1");
//     A.connect(&hub);
//     B.connect(&hub);
//     hub.connect(&A);
//     hub.connect(&B);

//     A.send("1011011","MAC_B");
// }




//step 7 will be to implement carrier sensing and collision detection 
// #include "devices/EndDevice.h"
// #include "devices/Hub.h"
// #include "network/Channel.h"

// int main() {

//     EndDevice A("A","MAC_A");
//     EndDevice B("B","MAC_B");

//     Hub H1("H1");

//     A.connect(&H1);
//     H1.connect(&A);

//     B.connect(&H1);
//     H1.connect(&B);

//     cout << "\n===== TEST 1 : Normal Transmission =====\n\n";

//     Channel::busy = false;
//     Channel::collision = false;

//     A.send("101101","MAC_B");

//     cout << "\n===== TEST 2 : Carrier Sense (Channel Busy) =====\n\n";

//     Channel::busy = true;
//     Channel::collision = false;

//     A.send("101101","MAC_B");

//     cout << "\n===== TEST 3 : Collision Detection =====\n\n";

//     Channel::busy = false;
//     Channel::collision = true;

//     A.send("101101","MAC_B");

//     return 0;
// }





//step 8 will be to implement a simple sliding window protocol for reliable data transfer between end devices, including ACKs and retransmissions.
// #include "devices/EndDevice.h"
// #include "devices/Hub.h"
// #include "network/Channel.h"

// int main() {

//     EndDevice A("A","MAC_A");
//     EndDevice B("B","MAC_B");

//     Hub H1("H1");

//     // create star topology
//     A.connect(&H1);
//     H1.connect(&A);

//     B.connect(&H1);
//     H1.connect(&B);

//     cout << "\n===== Sliding Window Test =====\n\n";

//     Channel::busy = false;
//     Channel::collision = false;

//     // send multiple frames
//     A.send("101101","MAC_B");
//     A.send("111000","MAC_B");
//     A.send("110011","MAC_B");

//     // window should now be full
//     A.send("100111","MAC_B");
//     A.send("110111","MAC_B");

//     return 0;
// }







#include "devices/EndDevice.h"
#include "devices/Hub.h"
#include "network/Channel.h"
#include "network/AckBuffer.h"

void deliverACKs(Device* receiver) {

    while(!AckBuffer::buffer.empty()) {

        Frame ack = AckBuffer::buffer.front();
        AckBuffer::buffer.pop();

        receiver->receive(ack, receiver);
    }
}

int main() {

    EndDevice A("A","MAC_A");
    EndDevice B("B","MAC_B");

    Hub H1("H1");

    A.connect(&H1);
    H1.connect(&A);

    B.connect(&H1);
    H1.connect(&B);

    Channel::busy = false;
    Channel::collision = false;

    cout << "\n===== Sliding Window Demonstration =====\n\n";

    A.send("101101","MAC_B");
    A.send("111000","MAC_B");
    A.send("110011","MAC_B");

    // window should now be full
    A.send("100111","MAC_B");

    cout << "\n--- Delivering ACKs ---\n\n";

    deliverACKs(&A);

    // now window slides
    A.send("100111","MAC_B");

}
