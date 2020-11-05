#ifndef VERTHASH_H2_INCLUDED
#define VERTHASH_H2_INCLUDED
#include <stdlib.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

void verthash_hash(const unsigned char* input, const size_t input_size, unsigned char* output);
int init_verthash();

#ifdef __cplusplus
}
#endif

#endif