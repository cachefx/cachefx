#ifndef SCATTERCACHE_H_
#define SCATTERCACHE_H_

#include "AssocCache.h"
#include <memory>
#include <vector>

class ScatterCache : public Cache
{
public:
  static const char* CACHE_TYPESTR;

private:
  std::vector<std::vector<cacheEntry>> _cacheEntries;
  size_t _nSets;
  size_t _nWays;
  bool _invalidFirst;

  uint32_t* _key;

public:
  ScatterCache(size_t sets, size_t ways);
  virtual ~ScatterCache();

  const char* getCacheType() const override;
  size_t getNLines() const override;

  size_t getNSets() const override { return _nSets; };
  size_t getNWays() const override { return _nWays; };
  size_t getEvictionSetSize() const override { return _nWays; };
  size_t getGHMGroupSize() const override { return _nWays; };

  size_t getNumParams() const override;
  uint32_t getParam(size_t idx) const override;

  bool getInvalidFirst() const { return _invalidFirst; };
  void setInvalidFirst(bool invalidFirst) { _invalidFirst = invalidFirst; };

  int32_t hasCollision(tag_t cl1, const CacheContext& ctx1, tag_t cl2,
                       const CacheContext& ctx2) const override;

protected:
  int32_t readCl(tag_t cl, const CacheContext& context,
                 std::list<CacheResponse>& response) override;
  int32_t evictCl(tag_t cl, const CacheContext& context,
                  std::list<CacheResponse>& response) override;

private:
  virtual tag_t getIdx(tag_t cl, size_t way, const CacheContext& context) const;
  virtual void access(cacheEntry& ce){};
  virtual std::vector<cacheEntry*> getVirtualSet(tag_t cl,
                                                 const CacheContext& context);
  virtual std::vector<tag_t> getWayIndices(tag_t cl,
                                           const CacheContext& context) const;
  void initKeys();
};

#endif /* SCATTERCACHE_H_ */
