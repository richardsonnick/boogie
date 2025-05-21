#include <vector>

using Buffer = std::vector<uint8_t>;

namespace utils {
    #define WORD_LEN 32

    inline Buffer to_buffer(const std::string& s) {
        return Buffer(s.begin(), s.end());
    }

    /** 
     * The point of this padding is to make the length a multiple of 512.
     * SHA-1 sequentially processes blocks of 512 bits when computing the
     * message digest. 
     * Padding should be a '1' followed by `m` '0's followed by a 64-bit int
     * this should produce a message of length 512 * `n`. The 64-bit int is the
     * length of the original message. The padded message is then processed by
     * SHA-1 as `n` 512-bit blocks.
    */
    void sha1_pad(Buffer& buf) {
        uint64_t len = buf.size() * 8; // Num bits in original message
        // Append 1 (0x80)
        buf.push_back(0x80);

        // Pad with 0s
        // TODO add support for messsages > 512 bits.
        // This should append until you are 64 bits short of a multiple of 512.
        auto target = 512 - (2 * WORD_LEN);
        while (buf.size() % (target / 8) != 0) {
            buf.push_back(0x00);
        }

        // Append buf length to padded buf. 
        // This was found using my own blood sweat and tears.
        for (int i = 0; i < 8; ++i) {
            int shift = (7 - i) * 8;

            // Grab a byte by shifting over i times and masking.
            uint8_t byte = static_cast<uint8_t>((len >> shift) & 0xFF);

            buf.push_back(byte);
        }
    }
}