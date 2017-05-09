/**
 * @file crc32c.h
 * @brief Function prototypes for hardware-based CRC-32C calculation
 *
 * @author Anand Suresh <anandsuresh@gmail.com>
 */

#include <cstdint>
#include <cstdlib>



/// \brief Returns true if SSE4.2 instruction set is available
bool isSSE42Available();
/// \brief Initializes the CRC - 32C lookup table for software - based CRC calculation
void initCrcTable();
/// \brief Hardware based (SSE4.2) CRC calculation
uint32_t hwCrc32c(uint32_t initialCrc, const char *buf, size_t len);
/// \brief Software based CRC calculation
uint32_t swCrc32c(uint32_t initialCrc, const char *buf, size_t len);

