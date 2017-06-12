/*

MIT LICENCE: https://opensource.org/licenses/MIT
Copyright 2015
Anand Suresh <anandsuresh@gmail.com>
Christophe Meneboeuf <christophe@xtof.info>

*/


#ifndef SRC_CRC_HPP_
#define SRC_CRC_HPP_

#include <functional>
#include <vector>

namespace Crc32c
{

    bool IsHardwareAccelerationAvailable();

    /// \brief Singleton class computing a CRC32.
    ///
    ///        The compute operation use hardware SSE4.2 acceleration when available,
    ///        or a software fallback otherwise.
    class Crc
    {
    public:
        /// \brief Constructor
        Crc(const uint32_t init = 0u);
        /// \brief Default destructor
        ~Crc() = default;
        /// \brief Sets the CRC value
        inline void operator=(const uint32_t rhs) {
            _crc = rhs;
        }
        /// \brief Updates CRC computation
        inline Crc operator+(std::vector<char>& data) {
            _crc = _compute(_crc, data.data(), data.size());
            return *this;
        }
        /// \brief Updates CRC computation
        inline Crc operator+=(std::vector<char>& data) {
            *this = *this + data;
            return *this;
        }
        /// \brief Returns the CRC32 value
        inline uint32_t getValue() const {
            return _crc;
        }
        
    private:

        uint32_t _crc; ///< Current CRC. USed as an input value if the CRC is called many times

        bool _isHardAccelAvail = false; ///< True if SSE4.2 harware acceleration is available
        std::function<uint32_t(uint32_t, const char*, size_t)> _compute; ///< Hardware based or pure software function computing the CRC
        static Crc* _Instance;  ///< Single static instance
    };
}

#endif
