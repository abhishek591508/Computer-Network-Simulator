
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

#include "devices/EndDevice.h"

int main() {
    EndDevice A("A");
    EndDevice B("B");
    EndDevice C("C");

    // connections
    A.connect(&B);
    B.connect(&A);

    B.connect(&C);
    C.connect(&B);

    // test direct communication
    A.send("Hello B", &B);

    // test non-direct
    A.send("Hello C", &C);

    return 0;
}