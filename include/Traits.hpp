#ifndef INCLUDE_TRAITS_HPP_
#define INCLUDE_TRAITS_HPP_

#include <type_traits>
#include <vector>
#include <array>

namespace Crc32c
{
    namespace Traits
    {
        /// \brief Are the data contiguously layed out in memory?
        template<typename T>
        struct has_contiguous_memory : std::false_type {};

        template<typename T, typename U>
        struct has_contiguous_memory<std::vector<T, U>> : std::true_type {};

        template<typename T>
        struct has_contiguous_memory<std::vector<T>> : std::true_type {};

        template<typename T, std::size_t N>
        struct has_contiguous_memory <std::array<T, N>> : std::true_type {};
        
    } // namespace Traits

} // namespace Crc32c


#endif
