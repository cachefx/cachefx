#ifndef __TYPES_H__
#define __TYPES_H__ 1
#include <cstdint>

typedef uint64_t address_t;
typedef uint64_t tag_t;

static const tag_t TAG_NONE = ~0ULL;
static const tag_t TAG_INIT = ~0ULL - 1;
static const int32_t CACHE_LINE_SIZE = 64;

#endif //__TYPES_H__
