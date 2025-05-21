#include <gtest/gtest.h>

#include <util/utils.h>

TEST(UtilsTest, SanityTest) {
    std::string message = "abc";
    Buffer buf = utils::to_buffer(message);
    utils::sha1_pad(buf);

    EXPECT_EQ(buf.size(), 512 / 8);
}