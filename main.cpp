
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
#include "devices/EndDevice.h"
#include "devices/Hub.h"

int main() {

    EndDevice A("A", "MAC_A");
    EndDevice B("B", "MAC_B");
    EndDevice C("C", "MAC_C");

    Hub hub("H1");

    A.connect(&hub);
    hub.connect(&A);

    B.connect(&hub);
    hub.connect(&B);

    C.connect(&hub);
    hub.connect(&C);

    cout << "\n--- Frame Transmission Test ---\n\n";

    A.send("Hello B", "MAC_B");

}