#include <iostream>

#include <util/utils.h>

namespace hash::sha1 {
    std::string hash(const std::string& message) {
        Buffer buf = utils::to_buffer(message);
        return "hello!";
    }
}