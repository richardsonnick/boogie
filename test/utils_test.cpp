#include <gtest/gtest.h>

#include <util/utils.h>
#include <test/assets/words.h>

class UtilsPaddingTest
  : public ::testing::TestWithParam<std::string> {};

TEST_P(UtilsPaddingTest, SHA1PadTest) {
    const std::string& message = GetParam();
    Buffer buf = utils::to_buffer(message);
    utils::sha1_pad(buf);

    EXPECT_EQ(buf.size() % (utils::BLOCK_LEN / utils::BYTE_LEN), 0); // length should be blocks of 512 bits

    // Check message
    for (int i = 0; i < message.size(); i++) {
        EXPECT_EQ(buf[i], message[i]);
    }

    // Zero pad
    uint zero_pad_range = buf.size() - ((utils::WORD_LEN  * 2) / utils::BYTE_LEN);
    for (int i = message.size() + 1; i < zero_pad_range; i++) {
        EXPECT_EQ(buf[i], 0x00);
    }

    // Check encoded length
    uint64_t len = 0;
    const uint encoded_len_length = utils::WORD_LEN / utils::BYTE_LEN;
    for (int i = buf.size() - encoded_len_length; i < buf.size(); i++) {
        len <<= utils::BYTE_LEN;
        len |= buf[i];
    }
    EXPECT_EQ(len, message.size() * utils::BYTE_LEN);
}

INSTANTIATE_TEST_SUITE_P(
    UtilsPaddingTests,  UtilsPaddingTest,
    ::testing::ValuesIn(testing::test_vector)
);