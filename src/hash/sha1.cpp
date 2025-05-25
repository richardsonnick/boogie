#include "sha1.h"
#include <iostream>
#include <optional>
#include <cassert>
#include <sstream>

#include <util/utils.h>

namespace hash::sha1 {

    static std::string final(const Sha1_context ctx) {
        return utils::toString(ctx.H.data(), ctx.H.size());
    }

    template<typename InputStream>
    static std::string hash_stream(InputStream& is) {
        auto ctx = sha1::makeContext();
        const int buffer_size = 4096; // Stream in 4096 sized chunks
        std::vector<char> buffer(buffer_size);

        while(is.read(buffer.data(), buffer.size())) { // Read in 4096 byte sized chunks from stream
            process(ctx, buffer, is.gcount());
        }

        /**
         * InputSteam::read(data, size) attempts to read size bytes. 
         * InputSteam::gcount returns the number of bytes left.
         * Let's read the rest of the stream left over from the read operations.
         */
        if(is.gcount() > 0) { 
            process(ctx, buffer, is.gcount());
        }

        return final(ctx);
    }

    std::string hash(const std::string& data) {
        std::istringstream iss(data);
        return hash_stream(iss);
    }

    /** 
     * The point of this padding is to make the length a multiple of 512.
     * SHA-1 sequentially processes blocks of 512 bits when computing the
     * message digest. 
     * Padding should be a '1' followed by `m` '0's followed by a 64-bit int
     * this should produce a message of length 512 * `n`. The 64-bit int is the
     * length of the original message. The padded message is then processed by
     * SHA-1 as `n` 512-bit blocks.
     * 
     * Returns the size of the final padded buffer.
    */
    uint sha1_pad(std::vector<char>& buf, uint64_t len) {
        const size_t block_size = SHA1_BLOCK_LEN / utils::BYTE_LEN;
        size_t resize_len = ((len + block_size - 1) / block_size) * block_size;


        buf.resize(std::max(resize_len, block_size));
        assert(buf.size() % 64 == 0);
        uint i = len;
        auto append = [&i](std::vector<char>& buf, uint8_t elem) {
            buf[i++] = elem;
        };

        // Append 1 (0x80)
        append(buf, 0x80);

        // Pad with 0s
        // This should append until you are 64 bits (2 words) short of a multiple of 512.
        // This extra space is for the 2 word sized length the be appended.
        auto length_pad = (2 * SHA1_WORD_LEN) / utils::BYTE_LEN;
        while ((i + length_pad) % (SHA1_BLOCK_LEN / utils::BYTE_LEN) != 0) {
            append(buf, 0x00);
        }

        // Append buf length to padded buf. 
        auto bit_len = len * utils::BYTE_LEN;
        for (int j = 0; j < utils::BYTE_LEN; ++j) {
            int shift = ((utils::BYTE_LEN - 1) - j) * utils::BYTE_LEN;

            // Grab a byte by shifting over i times and masking.
            uint8_t byte = static_cast<uint8_t>((bit_len >> shift) & 0xFF);

            append(buf, byte);
        }

        return i;
    }

    std::shared_ptr<std::vector<uint32_t>> toMessageDigestBuffer(const std::vector<char>& padded_message, uint64_t padded_buffer_size) {
        std::vector<uint32_t> m_digest_buffer;
        size_t num_words = padded_buffer_size / 4;
        m_digest_buffer.reserve(num_words);

        for (size_t i = 0; i < num_words; ++i) {
            uint32_t w = 0;
            for (size_t j = 0; j < 4; ++j) {
                size_t byte_index = i * 4 + j; // Index should be shifted a word (4 bytes) and 'j' over.
                if (byte_index < padded_message.size()) {
                    w |= (static_cast<uint32_t>(static_cast<unsigned char>(padded_message[byte_index])) << ((3 - j) * 8));
                } else {
                    return nullptr;
                }
            }
            m_digest_buffer.push_back(w);
        }
        return std::make_shared<std::vector<uint32_t>>(m_digest_buffer);
    }

    Sha1_context makeContext() {
        Sha1_context ctx;
        // TODO find a more efficient way to zero init a buffer.
        for (size_t i = 0; i < ctx.w.size(); i++) {
            ctx.w[i] = 0;
        }
        return ctx;
    }

    std::optional<uint32_t> f(uint t, uint32_t B, uint32_t C, uint32_t D) {
        if (t <= 19) {
            return (B & C) | ((~B) & D);
        }
        if (t >= 20 && t <= 39) {
            return B ^ C ^ D;
        }
        if (t >= 40 && t <= 59) {
            return (B & C) | (B & D) | (C & D);
        }
        if (t >= 60 && t<= 79) {
            return B ^ C ^ D;
        }
        return std::nullopt;
    }

    // TODO could make this more performant.
    std::optional<uint32_t> K(int t) {
        if (t <= 19) {
            return K_1;
        } else if (t >= 20 && t <= 39) {
            return K_2;
        } else if (t >= 40 && t <= 59) {
            return K_3;
        } else if (t >= 60 && t <= 79) {
            return K_4;
        }
        return std::nullopt;
    }

    // TODO reference the chunk (data) instead of copy
    void process(Sha1_context& ctx, std::vector<char> data, size_t buffer_size) {
        uint64_t padded_buffer_size = sha1_pad(data, buffer_size);
        auto digest_buffer = toMessageDigestBuffer(data, padded_buffer_size);
        if (!digest_buffer) {
            // TODO err condition
            return;
        }
        //TODO the digest buffer does not need to be carried between stream iterations.
        // Remove Sha1_context::m 
        ctx.m = std::move(digest_buffer);

        // ctx.m has uint32_t elements
        const auto words_per_block = SHA1_BLOCK_LEN / SHA1_WORD_LEN;
        // For each block
        for (size_t block_index = 0; block_index < ctx.m->size() / words_per_block; block_index++) {
            ctx.b1[0] = ctx.H[0];
            ctx.b1[1] = ctx.H[1];
            ctx.b1[2] = ctx.H[2];
            ctx.b1[3] = ctx.H[3];
            ctx.b1[4] = ctx.H[4];

            uint32_t& A = ctx.b1[0];
            uint32_t& B = ctx.b1[1];
            uint32_t& C = ctx.b1[2];
            uint32_t& D = ctx.b1[3];
            uint32_t& E = ctx.b1[4];

            // Load the current 16 words of the block into w[0]..w[15]
            for (int i = 0; i < words_per_block; i++) {
                size_t word_index = block_index * words_per_block + i;
                ctx.w[i] = (*ctx.m)[word_index];
            }

            /**
             * b. For t = 16 to 79 let
             *  W(t) = S^1(W(t-3) XOR W(t-8) XOR W(t-14) XOR W(t-16)).
             */
            for (int t = 16; t <= 79; t++) {
                uint32_t w_t = ctx.w[t - 3] ^ ctx.w[t - 8] ^ ctx.w[t - 14]  ^ ctx.w[t - 16];
                w_t = (w_t << 1) | (w_t >> (32 - 1));
                ctx.w[t] = w_t;
            }

            /**
             * d. For t = 0 to 79 do
             *   TEMP = S^5(A) + f(t;B,C,D) + E + W(t) + K(t);
             *   E = D;  D = C;  C = S^30(B);  B = A; A = TEMP;
             */
            for (int t = 0; t <= 79; t++) {
                ctx.temp = ((A << 5) | (A >> (32 - 5))) // S^5(A)
                        + f(t, B, C, D).value()      // f(t; B, C, D)
                        + E                          // + E
                        + ctx.w[t]                   // + W(t)
                        + K(t).value();              // + K(t)

                // Update registers
                E = D;
                D = C;
                C = (B << 30) | (B >> (32 - 30)); // S^30(B)
                B = A;
                A = ctx.temp;
            }

            //e. Let H0 = H0 + A, H1 = H1 + B, H2 = H2 + C, H3 = H3 + D, H4 = H4 + E.
            ctx.H[0] += A;
            ctx.H[1] += B;
            ctx.H[2] += C;
            ctx.H[3] += D;
            ctx.H[4] += E;
        }
    }
}