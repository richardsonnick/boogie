#include <gtest/gtest.h>

#include <util/utils.h>
#include <test/assets/words.h>

class UtilsPaddingTest
  : public ::testing::TestWithParam<std::string> {};

TEST_P(UtilsPaddingTest, SHA1PadTest) {
    const std::string& message = GetParam();
    Buffer buf = utils::to_buffer(message);
    utils::sha1_pad(buf);

    EXPECT_EQ(buf.size() % (512 / 8), 0); // length should be blocks of 512 bits

    // Check message
    for (int i = 0; i < message.size(); i++) {
        EXPECT_EQ(buf[i], message[i]);
    }

    // Zero pad
    for (int i = message.size() + 1; i < buf.size() - (64 / 8); i++) {
        EXPECT_EQ(buf[i], 0x00);
    }

    // Check encoded length
    uint64_t len = 0;
    for (int i = buf.size() - 4; i < buf.size(); i++) {
        len <<= 8;
        len |= buf[i];
    }
    EXPECT_EQ(len, message.size() * 8);
}

INSTANTIATE_TEST_SUITE_P(
    UtilsPaddingTests,  UtilsPaddingTest,
    ::testing::ValuesIn(testing::test_vector)
);