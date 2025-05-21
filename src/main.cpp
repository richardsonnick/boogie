#include <iostream>
#include "hash/sha1.h"

int main(void) {
    std::string message = "Hash me please!";
    std::string result = hash::sha1::hash(message);
    std::cout << result << std::endl;
    return 0;
}