#ifndef CACHEHIERARCHY_H_
#define CACHEHIERARCHY_H_

#include <Cache/Cache.h>
#include <memory>
#include <types.h>
#include <vector>

class CacheHierarchy : public Cache
{
public:
  static const char* CACHE_TYPESTR;

public:
  CacheHierarchy();
  virtual ~CacheHierarchy();

  int32_t hasCollision(tag_t cl1, const CacheContext& ctx1, tag_t cl2,
                       const CacheContext& ctx2) const override;
  const char* getCacheType() const override { return CACHE_TYPESTR; }

  Cache* getCache(uint32_t level);
  size_t getCacheLevels() const { return _cacheHierarchy.size(); }
  void setCacheLevels(std::vector<std::unique_ptr<Cache>> caches);
  void addCacheLevel(std::unique_ptr<Cache> cache);
  void moveCacheUp(uint32_t level);
  void moveCacheDown(uint32_t level);
  void removeCacheLevel(uint32_t level);
  void replaceCacheLevel(std::unique_ptr<Cache> cache, uint32_t level);

  void printHierarchy() const;

  size_t getNLines() const override;
  size_t getNSets() const override;
  size_t getNWays() const override;

  replAlg getAlgorithm() const override;
  size_t getEvictionSetSize() const override;
  size_t getGHMGroupSize() const override;
  size_t getNumParams() const override;
  uint32_t getParam(size_t idx) const override;

protected:
  int32_t readCl(tag_t cl, const CacheContext& context,
                 std::list<CacheResponse>& response) override;
  int32_t writeCl(tag_t cl, const CacheContext& context,
                  std::list<CacheResponse>& response) override;
  int32_t execCl(tag_t cl, const CacheContext& context,
                 std::list<CacheResponse>& response) override;
  int32_t evictCl(tag_t cl, const CacheContext& context,
                  std::list<CacheResponse>& response) override;

private:
  std::vector<std::unique_ptr<Cache>> _cacheHierarchy;
};

#endif /* CACHEHIERARCHY_H_ */
