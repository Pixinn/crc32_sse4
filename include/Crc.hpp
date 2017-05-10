/*

MIT LICENCE: https://opensource.org/licenses/MIT
Copyright 2015
Anand Suresh <anandsuresh@gmail.com>
Christophe Meneboeuf <christophe@xtof.info>

*/


#ifndef SRC_CRC_HPP_
#define SRC_CRC_HPP_

#include <functional>

namespace Crc32c
{
    /// \brief Singleton class computing a CRC32.
    ///
    ///        The compute operation use hardware SSE4.2 acceleration when available,
    ///        or a software fallback otherwise.
    class Crc
    {
    public:
        /// \brief Default destructor
        ~Crc() = default;
        /// \Returns the single instance of the class
        static const Crc& GetInstance();
        /// \brief Returns the CRC32 of the provided buf.
        inline uint32_t compute(const char *buf, const size_t len) const {
            return _compute(0, buf, len);
        }
        /// \brief Returns true if hardware acceleration is supported
        inline bool isHardAccelAvail() const {
            return _isHardAccelAvail;
        }
        
    private:
        Crc();

        bool _isHardAccelAvail = false; ///< True if SSE4.2 harware acceleration is available
        std::function<uint32_t(uint32_t, const char*, size_t)> _compute; ///< Hardware based or pure software function computing the CRC
        static Crc* _Instance;  ///< Single static instance
    };
}

#endif
