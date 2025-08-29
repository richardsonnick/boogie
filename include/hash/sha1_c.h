#ifndef SHA1_C_H
#define SHA1_C_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

int sha1_hash_string(const char* input, char* output);

int sha1_hash_file(const char* filepath, char* output);

int sha1_hash_data(const void* data, size_t length, char* output);

#ifdef __cplusplus
}
#endif

#endif /* SHA1_C_H */
