#include <iostream>
#include <optional>
#include <memory>
#include <sstream>
#include <vector>
#include <iomanip>

#pragma once

namespace hash::sha1 {
    // This could be a macro to allow for compile time config for systems with small memory resources.
    // (fsstream could read from disk)
    // NOTE should prob assert that this chunk size is > block size
    constexpr size_t CHUNK_SIZE = 1024;
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
        std::array<uint32_t, 5> H = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};
        std::array<uint32_t, 80> w;
        uint32_t temp;

        std::shared_ptr<std::vector<uint32_t>> m; // Message digest buffer. Split into 16 word (512 bits) blocks
        uint64_t message_len;
    };
    Sha1_context makeContext();
    std::string hash_string(const std::string& s);
    std::string hash_file(const std::string& path);
    uint sha1_pad(std::vector<char>& buf, uint64_t message_end_pos, uint64_t message_len);
    std::shared_ptr<std::vector<uint32_t>> toMessageDigestBuffer(const std::vector<char>& padded_message, uint64_t padded_buffer_size);
    void process(Sha1_context& ctx, std::vector<char> data, size_t buffer_size, bool is_last_chunk);

    static inline std::string final(const Sha1_context ctx) {
        const uint32_t* data(ctx.H.data());
        std::stringstream ss;
        ss << std::hex << std::setfill('0'); // Set output to hexadecimal and pad with 0

        for (size_t i = 0; i < ctx.H.size(); ++i) {
            uint32_t val = data[i];
            // Each uint32_t is 8 hex characters (4 bytes * 2 hex chars/byte)
            ss << std::setw(8) << val;
        }
        return ss.str();
    }

    template<typename InputStream>
    static std::string hash_stream(InputStream& is) {
        auto ctx = sha1::makeContext();

        if (is.peek() == EOF) { // is.read() will fail for empty input streams
            std::vector<char> empty_buffer;
            process(ctx, empty_buffer, is.gcount(), true);
            return final(ctx);
        }

        std::vector<char> buffer(CHUNK_SIZE);
        while(is.read(buffer.data(), buffer.size())) { // Read in 4096 byte sized chunks from stream
            process(ctx, buffer, is.gcount(), false);
        }

        /**
         * InputSteam::read(data, size) attempts to read size bytes. 
         * InputSteam::gcount returns the number of bytes left.
         * Let's read the rest of the stream left over from the read operations.
         */
        if(is.gcount() > 0) { 
            process(ctx, buffer, is.gcount(), true);
        }

        return final(ctx);
    }

}
