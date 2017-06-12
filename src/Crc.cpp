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

    bool IsHardwareAccelerationAvailable()
    {
        return isSSE42Available();
    }


    Crc::Crc(const uint32_t init) :
        _crc{init}
    {
        if (IsHardwareAccelerationAvailable()) {
            _compute = hwCrc32c;
            _isHardAccelAvail = true;
        }
        else {
            initCrcTable();
            _compute = swCrc32c;
        }
    }


}