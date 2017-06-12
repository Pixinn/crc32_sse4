#include <iostream>
#include <string>

#include "Crc.hpp"

using namespace std;

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    //const string str_1{ "SSE4-CRC32: A hardware accelerated CRC32 implementation for node.js" };
    //const string str_2{ "123456789" };
    //
    //auto crc32 = Crc32c::Crc::GetInstance();
    //const auto checksum_1 = crc32.compute(str_1.data(), str_1.size());
    //const auto checksum_2 = crc32.compute(str_2.data(), str_2.size());
    //
    const string method = Crc32c::IsHardwareAccelerationAvailable() ? "hardware" : "no hardware";
    cout << method << " acceleration available.\n";

    Crc32c::Crc crc1{ 0u };
    Crc32c::Crc crc2{ 0u };
    
    std::vector<char> vect1_1;
    {
        const char* str1 = "SSE4-CRC32: A hardware accelerated";
        for (auto i = 0u; str1[i] != '\0'; ++i) {
            vect1_1.push_back(str1[i]);
        }
    }
    std::vector<char> vect1_2;
    {
        const char* str1 = " CRC32 implementation for node.js";
        for (auto i = 0u; str1[i] != '\0'; ++i) {
            vect1_2.push_back(str1[i]);
        }
    }
    crc1 += vect1_1;
    crc1 += vect1_2;

    std::vector<char> vect2;
    {
        const char* str2 = "123456789";
        for (auto i = 0u; str2[i] != '\0'; ++i) {
            vect2.push_back(str2[i]);
        }
    }
    crc2 += vect2;


    if(crc1.getValue() == 3039989317 && crc2.getValue() == 0xe3069283) { //http://reveng.sourceforge.net/crc-catalogue/17plus.htm#crc.cat.crc-32c
        cout << "SUCCESS!\n";
        return 0;
    }
    else {
        cout << "FAILURE!\n";
        return -1;
    }



}