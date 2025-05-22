#include <gtest/gtest.h>

#include <src/hash/sha1.h>
#include <test/assets/words.h>

using namespace hash;
class SHA1Tests
  : public ::testing::TestWithParam<std::string> {};

TEST(SHA1Tests, MakeContextTest) {
    const std::string& message = "I need context!";
    auto gotContext = sha1::makeContext(message);
    ASSERT_TRUE(gotContext);
    EXPECT_EQ(gotContext->b1.size(), 5);
    for (auto elem : gotContext->b1) {
        EXPECT_EQ(elem, 0x0);
    }
    EXPECT_EQ(gotContext->H.size(), 5);
    EXPECT_EQ(gotContext->w.size(), 80);
}

TEST(SHA1Tests, DigestAtTest) {
    auto buffer = std::make_shared<std::vector<uint32_t>>();
    for (int i = 0; i < 4; i++) {
        buffer->push_back(0xDEADBEEF);
        for (int j = 1; j < sha1::SHA1_BLOCK_LEN / sha1::SHA1_WORD_LEN; j++) {
            buffer->push_back(0x00);
        }
    }

    auto gotInt = sha1::digestAt(buffer, 1);
    ASSERT_TRUE(gotInt.has_value());
    EXPECT_EQ(*gotInt.value(), 0xDEADBEEF);
}

TEST_P(SHA1Tests, SHA1PadTest) {
    const std::string& message = GetParam();
    Buffer buf = utils::to_buffer(message);
    sha1::sha1_pad(buf);

    EXPECT_EQ(buf.size() % (sha1::SHA1_BLOCK_LEN / utils::BYTE_LEN), 0); // length should be blocks of 512 bits

    // Check message
    for (int i = 0; i < message.size(); i++) {
        EXPECT_EQ(buf[i], message[i]);
    }

    // Zero pad
    uint zero_pad_range = buf.size() - ((sha1::SHA1_WORD_LEN  * 2) / utils::BYTE_LEN);
    for (int i = message.size() + 1; i < zero_pad_range; i++) {
        EXPECT_EQ(buf[i], 0x00);
    }

    // Check encoded length
    uint64_t len = 0;
    const uint encoded_len_length = sha1::SHA1_WORD_LEN / utils::BYTE_LEN;
    for (int i = buf.size() - encoded_len_length; i < buf.size(); i++) {
        len <<= utils::BYTE_LEN;
        len |= buf[i];
    }
    EXPECT_EQ(len, message.size() * utils::BYTE_LEN);
}

TEST_P(SHA1Tests, ToMessageDigestBufferTest) {
    const std::string& message = GetParam();
    Buffer buf = utils::to_buffer(message);
    sha1::sha1_pad(buf); 
    auto got_buffer = sha1::toMessageDigestBuffer(buf);
    ASSERT_TRUE(got_buffer);

    // Each word should be 4 bytes
    ASSERT_EQ(buf.size() % 4, 0);
    ASSERT_EQ(got_buffer->size(), buf.size() / 4);

    // Check the words
    for (size_t i = 0; i < got_buffer->size(); i++) {
        uint32_t expectedWord = 0;
        for (size_t j = 0; j < 4; ++j) {
            expectedWord |= (static_cast<uint32_t>(buf[i * 4 + j]) << ((3 - j) * 8));
        }
        EXPECT_EQ(got_buffer->at(i), expectedWord);
    }
}

TEST(SHA1Tests, ProcessDigestTest) {
    const std::string& message = "";
    auto ctx = sha1::makeContext(message);
    ASSERT_TRUE(ctx.has_value());

    sha1::process(*ctx);
    std::string s = utils::toString(ctx->H.data(), ctx->H.size());
    EXPECT_EQ(s, "da39a3ee5e6b4b0d3255bfef95601890afd80709");
}

INSTANTIATE_TEST_SUITE_P(
    SHA1TestVector,  SHA1Tests,
    ::testing::ValuesIn(testing::test_vector)
);
