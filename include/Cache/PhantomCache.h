#ifndef PHANTOMCACHE_H_
#define PHANTOMCACHE_H_

#include <Cache/SetAssocCache.h>

class PhantomCache : public SetAssocCache
{
public:
  static const char* CACHE_TYPESTR;

  PhantomCache(int32_t nsets, int32_t nways, int32_t r)
      : PhantomCache(REPL_LRU, nsets, nways,
                     r){}; // r is the number of randomized sets
  PhantomCache(replAlg alg, int32_t nsets, int32_t nways, int32_t r);
  virtual ~PhantomCache();

  const char* getCacheType() const override { return CACHE_TYPESTR; }
  size_t getEvictionSetSize() const override { return nways * _r; };
  size_t getGHMGroupSize() const override { return nways; };

  size_t getNRandomSets() const { return _r; }

  size_t getNumParams() const override;
  uint32_t getParam(size_t idx) const override;

  int32_t hasCollision(tag_t cl1, const CacheContext& ctx1, tag_t cl2,
                       const CacheContext& ctx2) const override;

protected:
  AssocCache* getSet(tag_t tag) const override;

private:
  void initKeys();
  void generateSalts(int32_t r);
  tag_t getIdx(tag_t cl, int32_t r) const;

private:
  int32_t _r; // number of randomly selected sets
  uint32_t* _key;
  uint64_t* _salts;
};

#endif /* PANTOMCACHE_H_ */
