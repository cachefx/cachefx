#ifndef __SETASSOCCACHE_H__
#define __SETASSOCCACHE_H__ 1

#include <Cache/AssocCache.h>

class AssocCache;

class SetAssocCache : public Cache
{
public:
  static const char* CACHE_TYPESTR;

protected:
  AssocCache** sets;
  int32_t nsets;
  int32_t nways;
  replAlg algorithm;

  virtual AssocCache* getSet(tag_t tag) const { return sets[tag % nsets]; };

public:
  SetAssocCache(int32_t nsets, int32_t nways)
      : SetAssocCache(REPL_LRU, nsets, nways){};
  SetAssocCache(replAlg alg, int32_t nsets, int32_t nways);
  virtual ~SetAssocCache();

  size_t getNSets() const override { return nsets; };
  size_t getNWays() const override { return nways; };
  size_t getEvictionSetSize() const override { return nways; };
  size_t getGHMGroupSize() const override { return nways; };

  void setAlgorithm(replAlg alg);
  replAlg getAlgorithm() const override { return algorithm; }

  const char* getCacheType() const override { return CACHE_TYPESTR; }

  size_t getNLines() const override { return nsets * nways; }

  int32_t hasCollision(tag_t cl1, const CacheContext& ctx1, tag_t cl2,
                       const CacheContext& ctx2) const override;

protected:
  int32_t readCl(tag_t cl, const CacheContext& context,
                 std::list<CacheResponse>& response) override
  {
    return getSet(cl)->read(cl, context, response);
  };
  int32_t evictCl(tag_t cl, const CacheContext& context,
                  std::list<CacheResponse>& response) override
  {
    return getSet(cl)->evict(cl, context, response);
  };
  int32_t writeCl(tag_t cl, const CacheContext& context,
                  std::list<CacheResponse>& response) override
  {
    return getSet(cl)->write(cl, context, response);
  };
  int32_t execCl(tag_t cl, const CacheContext& context,
                 std::list<CacheResponse>& response) override
  {
    return getSet(cl)->exec(cl, context, response);
  };
};

#endif // __SETASSOCCACHE_H__
