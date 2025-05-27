#include <iostream>
#include <string>
#include <sstream>

#include "hash/sha1.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <hash_function>\n";
        std::cerr << "  Available hash functions: sha1\n";
        return 1;
    }

    std::string hash_function = argv[1];
    std::string input;
    std::stringstream buffer;

    // Read from stdin
    buffer << std::cin.rdbuf();
    input = buffer.str();

    if (hash_function == "sha1") {
        std::cout << hash::sha1::hash_string(input) << std::endl;
    } else {
        std::cerr << "Error: Unknown hash function '" << hash_function << "'\n";
        return 1;
    }

    return 0;
}
