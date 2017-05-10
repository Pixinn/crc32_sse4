# Crc32c-SSE4

This library computes CRC32 checksum (*Castagnoli* variant).
The calculations take advantage of the **SSE4.2** instruction set if available.

## Features

- Intel Streaming SIMD Extensions 4.2 based hardware accelerated CRC-32C calculation
- Graceful fallback to software-based CRC (table-based CRC calculation)
- Progressive CRC-32C calculation
