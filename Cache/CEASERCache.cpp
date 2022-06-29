#include <Cache/CEASERCache.h>
#include <crypto/speck.h>
#include <iostream>

const char* CEASERCache::CACHE_TYPESTR = "ceaser";

void CEASERCache::initKeys()
{
  // ASAN overflow: speck64ExpandKey() accesses 4th
  // element of type uint32_t*
  uint32_t K[] = {0xDEADBEEF, 0x000CAFFE, 0x47111174, 0x08155180};

  _key = new uint32_t[27];

  speck64ExpandKey(K, _key);
}

AssocCache* CEASERCache::getSet(tag_t cl) const { return sets[getIdx(cl)]; }

tag_t CEASERCache::getIdx(tag_t cl) const
{
  uint64_t v;
  uint32_t* vPtr = (uint32_t*)&v;

  v = cl & 0xFFFFFFFFFFFFFFFF;

  speck64Encrypt(vPtr + 0, vPtr + 1, _key);

  return v % nsets;
}
