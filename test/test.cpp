#include <iostream>
#include <string>

#include "Crc.hpp"

using namespace std;

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    const string str_1{ "SSE4-CRC32: A hardware accelerated CRC32 implementation for node.js" };
    const string str_2{ "123456789" };
    
    auto crc32 = Crc32c::Crc::GetInstance();
    const auto checksum_1 = crc32.compute(str_1.data(), str_1.size());
    const auto checksum_2 = crc32.compute(str_2.data(), str_2.size());
    
    const string method = crc32.isHardAccelAvail() ? "hardware" : "no hardware";
    cout << method << " acceleration available.\n";
    if(checksum_1 == 3039989317 && checksum_2 == 0xe3069283) { //http://reveng.sourceforge.net/crc-catalogue/17plus.htm#crc.cat.crc-32c
        cout << "SUCCESS!\n";
        return 0;
    }
    else {
        cout << "FAILURE!\n";
        return -1;
    }

}