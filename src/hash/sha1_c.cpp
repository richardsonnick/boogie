#include "hash/sha1_c.h"
#include "hash/sha1.h"
#include <cstring>
#include <sstream>
#include <stdexcept>

extern "C" {

int sha1_hash_string(const char* input, char* output) {
    if (!input || !output) {
        return -1;
    }
    
    try {
        std::string result = hash::sha1::hash_string(std::string(input));
        if (result.length() != 40) {
            return -1;
        }
        std::strcpy(output, result.c_str());
        return 0;
    } catch (...) {
        return -1;
    }
}

int sha1_hash_file(const char* filepath, char* output) {
    if (!filepath || !output) {
        return -1;
    }
    
    try {
        std::string result = hash::sha1::hash_file(std::string(filepath));
        if (result.length() != 40) {
            return -1;
        }
        std::strcpy(output, result.c_str());
        return 0;
    } catch (...) {
        return -1;
    }
}

int sha1_hash_data(const void* data, size_t length, char* output) {
    if (!data || !output) {
        return -1;
    }
    
    try {
        std::string input(static_cast<const char*>(data), length);
        std::string result = hash::sha1::hash_string(input);
        if (result.length() != 40) {
            return -1;
        }
        std::strcpy(output, result.c_str());
        return 0;
    } catch (...) {
        return -1;
    }
}

} // extern "C"
