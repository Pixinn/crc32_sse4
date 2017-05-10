/*

MIT LICENCE: https://opensource.org/licenses/MIT
Copyright 2015
Anand Suresh <anandsuresh@gmail.com>
Christophe Meneboeuf <christophe@xtof.info>

*/

#include "crc32c.h"

#include "Crc.hpp"

namespace Crc32c
{
    Crc* Crc::_Instance = nullptr;

    Crc::Crc()
    {
        if (isSSE42Available()) {
            _compute = hwCrc32c;
            _isHardAccelAvail = true;
        }
        else {
            initCrcTable();
            _compute = swCrc32c;
        }
    }


    const Crc& Crc::GetInstance()
    {
        // TODO Add a mutex
        if (_Instance == nullptr) {
            _Instance = new Crc();
        }
        return *_Instance;
    }

}