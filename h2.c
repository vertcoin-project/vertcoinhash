#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "tiny_sha3/sha3.h"

#define HEADER_SIZE 80
#define HASH_OUT_SIZE 32
#define P0_SIZE 64
#define N_ITER 8 
#define N_SUBSET P0_SIZE*N_ITER
#define N_ROT 32
#define N_INDEXES 4096
#define BYTE_ALIGNMENT 16

const char* dat_file_name = "verthash.dat";
const char* input_header_hex = "000000203a297b4b7685170d7644b43e5a6056234cc2414edde454a87580e1967d14c1078c13ea916117b0608732f3f65c2e03b81322efc0a62bcee77d8a9371261970a58a5a715da80e031b02560ad8";
int blob_initialized = 0;
unsigned char* blob_bytes;
size_t blob_size;

static inline uint32_t fnv1a(const uint32_t a, const uint32_t b) {
    return (a ^ b) * 0x1000193;
}

void verthash_hash(const unsigned char* input, const size_t input_size, unsigned char* output) {
    unsigned char p1[HASH_OUT_SIZE];
    sha3(&input[0], input_size, &p1[0], HASH_OUT_SIZE);

    unsigned char p0[N_SUBSET];

    unsigned char input_header[input_size];
    memcpy(input_header, input, input_size);

    for(size_t i = 0; i < N_ITER; i++) {
    	input_header[0] += 1;
    	sha3(&input_header[0], input_size, p0+i*P0_SIZE, P0_SIZE);
    }

    uint32_t* p0_index = (uint32_t*)p0;
    uint32_t seek_indexes[N_INDEXES];

    for(size_t x = 0; x < N_ROT; x++) {
    	memcpy(seek_indexes+x*(N_SUBSET/sizeof(uint32_t)), p0, N_SUBSET);
    	for(size_t y = 0; y < N_SUBSET/sizeof(uint32_t); y++) {
	        *(p0_index + y) = (*(p0_index + y) << 1) | (1 & (*(p0_index + y) >> 31));
	    }
    }

    uint32_t* p1_32 = (uint32_t*)p1;
    uint32_t* blob_bytes_32 = (uint32_t*)blob_bytes;
    uint32_t value_accumulator = 0x811c9dc5;
    const uint32_t mdiv = ((blob_size - HASH_OUT_SIZE)/BYTE_ALIGNMENT) + 1;
    for(size_t i = 0; i < N_INDEXES; i++) {
        const uint32_t offset = (fnv1a(seek_indexes[i], value_accumulator) % mdiv) * BYTE_ALIGNMENT/sizeof(uint32_t); 
        for(size_t i2 = 0; i2 < HASH_OUT_SIZE/sizeof(uint32_t); i2++) {
            const uint32_t value = *(blob_bytes_32 + offset + i2);
            uint32_t* p1_ptr = p1_32 + i2;
            *p1_ptr = fnv1a(*p1_ptr, value);

            value_accumulator = fnv1a(value_accumulator, value);
        }
    }

    memcpy(output, p1, HASH_OUT_SIZE);
}

int init_verthash() {
    if(blob_initialized == 1) return 0;

    FILE* datfile = fopen(dat_file_name, "rb");
    fseek(datfile, 0, SEEK_END);
    blob_size = ftell(datfile);

    fseek(datfile, 0, SEEK_SET);
    
    blob_bytes = malloc(blob_size);

    const size_t bytes_read = fread(blob_bytes, 1, blob_size, datfile);
    if(bytes_read != blob_size) {
        return -1;
    }

    fclose(datfile);

    blob_initialized = 1;
    return 0;
}

