#include <vector>

using Buffer = std::vector<uint8_t>;

namespace utils {

    inline Buffer toBuffer(const std::string& s) {
        return Buffer(s.begin(), s.end());
    }

    Buffer pad(Buffer buf, uint padding) {

    }
}