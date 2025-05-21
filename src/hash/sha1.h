#include <iostream>

#include <util/utils.h>

namespace hash::sha1 {
    std::string hash(const std::string& message) {
        Buffer buf = utils::toBuffer(message);
        return "hello!";
    }
}