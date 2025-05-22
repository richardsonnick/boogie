#include <vector>

using Buffer = std::vector<uint8_t>;

namespace utils {
    // Lengths in bits
    constexpr int BYTE_LEN = 8;

    inline Buffer to_buffer(const std::string& s) {
        return Buffer(s.begin(), s.end());
    }
}