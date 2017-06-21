/*

MIT LICENCE: https://opensource.org/licenses/MIT
Copyright 2015-2017
@author Anand Suresh <anandsuresh@gmail.com>
@author Christophe Meneboeuf <christophe@xtof.info> for the C++ wrapper

*/


#ifndef INCLUDE_CRC_HPP_
#define INCLUDE_CRC_HPP_

#include <functional>
#include <iterator>

#include "Traits.hpp"

namespace Crc32c
{

    /// \brief Returns true if hardware acceleration is available
    bool IsHardwareAccelerationAvailable();

    //////////////////////////
    /// \brief Computes a CRC32 (*Castagnoli* variant)
    ///
    ///        The *process* operation relies on hardware SSE4.2 acceleration when available,
    ///        or a software fallback otherwise.
    ///
    ///        Operates on **containers** providing **const_iterator**.<br/>
    ///        The computation can be called iteratively on "adjacent and ordered data".<br/>
    ///        **Note**: If the data carried by the collection is not 8bit wide, the CRC computed will depend
    ///        on the endianness of the computer.
    ///
    //////////////////////////
    class Crc
    {
    public:

        /// \brief Constructor
        Crc(const uint32_t init = 0u);
        /// \brief Default destructor
        ~Crc() = default;


        /// \brief Sets the CRC value
        ///
        ///        Can be used to reset the CRC computation by setting with 0.
        inline void operator=(const uint32_t rhs) {
            _crc = rhs;
        }


        ///////////////////////////////////////
        /// \brief Updates CRC computation with data between two iterators
        ///
        ///        *NOTE:* Data carried by the container **must be layed out contiguouly in memory**!
        /// \tparam CONTAINER_T A containder that provide const_iterator
        ///////////////////////////////////////
        template<typename CONTAINER_T>
        inline Crc& process(typename CONTAINER_T::const_iterator it_beg, typename CONTAINER_T::const_iterator it_end)
        {
            static_assert(Traits::has_contiguous_memory<CONTAINER_T>::value,
                "Data carried by the container must be layed out contiguouly in memory!");
            const auto begin = reinterpret_cast<const char*>(&(*it_beg));
            const auto end = reinterpret_cast<const char*>(&(*it_end));
            const auto size = end - begin;
            _crc = _compute(_crc, begin, size);
            return *this;
        }

        ///////////////////////////////////////
        /// \brief  Updates CRC computation with data from a container.
        /// \tparam CONTAINER_T A containder that can be argument to std::begin and std::end
        ///////////////////////////////////////
        template<typename CONTAINER_T>
        inline Crc& operator<<(const CONTAINER_T& data)
        {
            return process<CONTAINER_T>(std::begin(data), std::end(data));
        }


        /// \brief Returns the CRC32 value
        inline uint32_t getValue() const {
            return _crc;
        }

    private:

        uint32_t _crc; ///< Current CRC. USed as an input value if the CRC is called many times

        bool _isHardAccelAvail = false; ///< True if SSE4.2 harware acceleration is available
        std::function<uint32_t(uint32_t, const char*, size_t)> _compute; ///< Hardware based or pure software function computing the CRC
    };
}

#endif
