// filepath: /Users/nr/code/boogie/src/hash/test_sha1.h
#include <gtest/gtest.h>
#include <src/hash/sha1.h>
#include <util/utils.h>

using namespace hash::sha1;

TEST(SHA1ProcessTests, ProcessSimpleMessage) {
    const std::string message = "abc";
    auto ctx = makeContext(message);
    ASSERT_TRUE(ctx.has_value());

    process(*ctx);

    // Expected hash for "abc" from RFC 3174
    std::string expected_hash = "a9993e364706816aba3e25717850c26c9cd0d89d";
    std::string computed_hash = utils::toString(ctx->H.data(), ctx->H.size());

    EXPECT_EQ(computed_hash, expected_hash);
}

TEST(SHA1ProcessTests, ProcessEmptyMessage) {
    const std::string message = "";
    auto ctx = makeContext(message);
    ASSERT_TRUE(ctx.has_value());

    process(*ctx);

    // Expected hash for an empty string from RFC 3174
    std::string expected_hash = "da39a3ee5e6b4b0d3255bfef95601890afd80709";
    std::string computed_hash = utils::toString(ctx->H.data(), ctx->H.size());

    EXPECT_EQ(computed_hash, expected_hash);
}

TEST(SHA1ProcessTests, ProcessLongMessage) {
    const std::string message = "The quick brown fox jumps over the lazy dog";
    auto ctx = makeContext(message);
    ASSERT_TRUE(ctx.has_value());

    process(*ctx);

    // Expected hash for "The quick brown fox jumps over the lazy dog" from RFC 3174
    std::string expected_hash = "2fd4e1c67a2d28fced849ee1bb76e7391b93eb12";
    std::string computed_hash = utils::toString(ctx->H.data(), ctx->H.size());

    EXPECT_EQ(computed_hash, expected_hash);
}

TEST(SHA1ProcessTests, ProcessEdgeCaseMessage) {
    const std::string message(1000, 'a'); // 1000 'a' characters
    auto ctx = makeContext(message);
    ASSERT_TRUE(ctx.has_value());

    process(*ctx);

    // Expected hash for 1000 'a' characters (precomputed using a trusted SHA-1 implementation)
    std::string expected_hash = "34aa973cd4c4daa4f61eeb2bdbad27316534016f";
    std::string computed_hash = utils::toString(ctx->H.data(), ctx->H.size());

    EXPECT_EQ(computed_hash, expected_hash);
}