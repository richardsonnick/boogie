#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip> // Required for std::hex, std::setfill, std::setw

using Buffer = std::vector<uint8_t>;

namespace utils {
    // Lengths in bits
    constexpr int BYTE_LEN = 8;

    std::string toString(const uint32_t* data, size_t size);

    inline Buffer to_buffer(const std::string& s) {
        return Buffer(s.begin(), s.end());
    }
}

#endif // UTILS_H