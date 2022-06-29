#ifndef CEASERCACHE_H_
#define CEASERCACHE_H_

#include <Cache/SetAssocCache.h>

class CEASERCache : public SetAssocCache
{
public:
  static const char* CACHE_TYPESTR;

  CEASERCache(int32_t nsets, int32_t nways)
      : CEASERCache(REPL_LRU, nsets, nways){};
  CEASERCache(replAlg alg, int32_t nsets, int32_t nways)
      : SetAssocCache(alg, nsets, nways)
  {
    initKeys();
  };
  virtual ~CEASERCache() { delete[] _key; };

  const char* getCacheType() const override { return CACHE_TYPESTR; }
  size_t getEvictionSetSize() const override { return nways; };
  size_t getGHMGroupSize() const override { return nways; };

protected:
  virtual AssocCache* getSet(tag_t tag) const;

private:
  void initKeys();
  tag_t getIdx(tag_t cl) const;

private:
  uint32_t* _key;
};

#endif /* CEASERCACHE_H_ */
