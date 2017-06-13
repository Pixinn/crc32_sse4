#include <iostream>
#include <string>

#include "Crc.hpp"

using namespace std;

int main(int, char**)
{
    const string method = Crc32c::IsHardwareAccelerationAvailable() ? "hardware" : "no hardware";
    cout << method << " acceleration available.\n";

    // Strings & CRC values: http://reveng.sourceforge.net/crc-catalogue/17plus.htm#crc.cat.crc-32c
    const string str1{"SSE4-CRC32: A hardware accelerated CRC32 implementation for node.js"};
    const string str2{"123456789"};
    const auto crc_str1 = 0xb5328e45;
    const auto crc_str2 = 0xe3069283;

    // TEST 1 - 1st string straighforward
    std::vector<char> vect1;
    std::copy(std::begin(str1), std::end(str1), std::back_inserter(vect1));
    Crc32c::Crc crc1;
    crc1 << vect1;
    const auto result_1 = (crc1.getValue() == crc_str1);

    // TEST 2 - 2nd string straighforward
    std::vector<char> vect2;
    std::copy(std::begin(str2), std::end(str2), std::back_inserter(vect2));
    crc1 = 0;
    auto crc2 = crc1;
    crc2 << vect2;
    const auto result_2 = (crc2.getValue() == crc_str2);

    // TEST 3 - 1st string splitted
    std::vector<char> vect3_1;
    std::vector<char> vect3_2;
    Crc32c::Crc crc3;
    auto result_3 = true;
    // Testing all the split positions
    for(auto pos_split = 1u; pos_split < str1.length(); ++pos_split) {
        vect3_1.clear();
        vect3_2.clear();
        crc3 = 0;
        std::copy(std::begin(str1), std::begin(str1)+pos_split, std::back_inserter(vect3_1));
        std::copy(std::begin(str1)+pos_split, std::end(str1), std::back_inserter(vect3_2));
        crc3 << vect3_1;
        crc3 << vect3_2;
        result_3 &= (crc3.getValue() == crc_str1);
    }

    if(result_1 && result_2 && result_3) {
        cout << "SUCCESS!\n";
        return 0;
    }
    else {
        cout << "FAILURE!\n";
        return -1;
    }
}
