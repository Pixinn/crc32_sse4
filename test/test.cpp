#include <iostream>
#include <string>

#include "crc32c.h"

using namespace std;

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    if (!isSSE42Available()) {
        cout << "SSE4.2 unsupported: cannot proced to hardware calculation.\nFAILURE!\n";
        return -1;
    }

    const string str("SSE4-CRC32: A hardware accelerated CRC32 implementation for node.js");
    
    const auto crcHw = hwCrc32c(0, str.data(), str.size());
    
    initCrcTable();
    const auto crcSw = swCrc32c(0, str.data(), str.size());

    cout << "RESULTS:\nHardware = " << to_string(crcHw) << "\nSoftware = " << to_string(crcSw);
    if (crcSw == crcHw) {
        cout << "\nSUCCESS!\n";
        return 0;
    }
    else {
        cout << "\nFAILURE!\n";
        return -1;
    }
}