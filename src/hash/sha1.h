#include <iostream>
#include <optional>

#include <util/utils.h>

namespace hash::sha1 {
    constexpr int SHA1_WORD_LEN = 32;
    constexpr int SHA1_BLOCK_LEN = 512;

    // These constants are part of the standard
    // https://datatracker.ietf.org/doc/html/rfc3174#section-5
    constexpr int K_1 = 0x5A827999;
    constexpr int K_2 = 0x6ED9EBA1;
    constexpr int K_3 = 0x8F1BBCDC;
    constexpr int K_4 = 0xCA62C1D6;

    struct Sha1_context {
        /**
         *    The message digest is computed using the message padded as described
         *    in section 4.  The computation is described using two buffers, each
         *    consisting of five 32-bit words, and a sequence of eighty 32-bit
         *    words.  The words of the first 5-word buffer are labeled A,B,C,D,E.
         *    The words of the second 5-word buffer are labeled H0, H1, H2, H3, H4.
         *    The words of the 80-word sequence are labeled W(0), W(1),..., W(79).
         *    A single word buffer TEMP is also employed.
         */
        std::array<uint32_t, 5> b1 = {0x0,0x0,0x0,0x0,0x0};
        std::array<uint32_t, 5> b2 = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};
        std::array<uint32_t, 80> w;
        std::vector<uint32_t> temp;

        std::vector<uint32_t> m; // Message digest buffer. Split into 16 word (512 bits) blocks
    };


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

    std::optional<std::vector<uint32_t>> toMessageDigestBuffer(const Buffer& padded_message) {
        std::vector<uint32_t> m_digest_buffer;
        size_t num_words = padded_message.size() / 4;
        m_digest_buffer.reserve(num_words);

        for (size_t i = 0; i < num_words; ++i) {
            uint32_t w = 0;
            for (size_t j = 0; j < 4; ++j) {
                size_t byte_index = i * 4 + j; // Index should be shifted a word (4 bytes) and 'j' over.
                if (byte_index < padded_message.size()) {
                    w |= (static_cast<uint32_t>(padded_message[byte_index]) << ((3 - j) * 8));
                } else {
                    return std::nullopt;
                }
            }
            m_digest_buffer.push_back(w);
        }
        return m_digest_buffer;
    }

    std::optional<Sha1_context> makeContext(const std::string& message) {
        Sha1_context ctx;
        Buffer buf = utils::to_buffer(message);
        sha1_pad(buf);
        auto digest_buffer = toMessageDigestBuffer(buf);
        if (!digest_buffer) {
            return std::nullopt;
        }
        ctx.m = digest_buffer.value();
        return ctx;
    }

    // Given a buffer digest (a vector of words), return a pointer to the block (521 bits) at i.
    std::optional<*uint32_t> digestAt(std::vector<uint32_t> buffer_digest, uint i) {
        auto block_index = i * sha1::SHA1_BLOCK_LEN;
        if (block_index >= buffer_digest.size()) {
            return std::nullopt;
        }
        return buffer_digest[i * sha1::SHA1_BLOCK_LEN];
    }

    std::string hash(const std::string& message) {
        Buffer buf = utils::to_buffer(message);
        return "Not implemented...";
    }



}