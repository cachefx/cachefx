#ifndef CRYPTO_SPECK_H_
#define CRYPTO_SPECK_H_

#include <cstdint>

void speck128Encrypt(uint64_t* u, uint64_t* v, uint64_t* key);

void speck128Decrypt(uint64_t* u, uint64_t* v, uint64_t* key);

void speck128ExpandKey(uint64_t* K, uint64_t* key);

void speck64Encrypt(uint32_t* u, uint32_t* v, uint32_t* key);

void speck64Decrypt(uint32_t* u, uint32_t* v, uint32_t* key);

void speck64ExpandKey(uint32_t* K, uint32_t* key);

#endif /* CRYPTO_SPECK_H_ */
