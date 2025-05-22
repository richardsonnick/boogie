#include <iostream>

#include <util/utils.h>

namespace hash::sha1 {
    constexpr int SHA1_WORD_LEN = 32;
    constexpr int SHA1_BLOCK_LEN = 512;

    std::string hash(const std::string& message) {
        Buffer buf = utils::to_buffer(message);
        return "Not implemented...";
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
        uint64_t len = buf.size() * utils::BYTE_LEN; // Num bits in original message
        // Append 1 (0x80)
        buf.push_back(0x80);

        // Pad with 0s
        // This should append until you are 64 bits (2 words) short of a multiple of 512.
        // This extra space is for the 2 word sized length the be appended.
        auto length_pad = (2 * SHA1_WORD_LEN) / utils::BYTE_LEN;
        while ((buf.size() + length_pad) % (SHA1_BLOCK_LEN / utils::BYTE_LEN) != 0) {
            buf.push_back(0x00);
        }

        // Append buf length to padded buf. 
        for (int i = 0; i < utils::BYTE_LEN; ++i) {
            int shift = ((utils::BYTE_LEN - 1) - i) * utils::BYTE_LEN;

            // Grab a byte by shifting over i times and masking.
            uint8_t byte = static_cast<uint8_t>((len >> shift) & 0xFF);

            buf.push_back(byte);
        }
    }
}