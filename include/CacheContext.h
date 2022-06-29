#ifndef CACHECONTEXT_H_
#define CACHECONTEXT_H_

#include <stdint.h>

class CacheContext
{
private:
  int32_t _coreId;

public:
  CacheContext();
  CacheContext(int32_t coreId);
  CacheContext(const CacheContext& ctx);
  virtual ~CacheContext();

  int32_t getCoreId() const { return _coreId; }
  void setCoreId(int32_t coreId) { _coreId = coreId; }

  bool operator==(const CacheContext& context) const;
  bool operator!=(const CacheContext& context) const;
};

class CacheContextCoreIdComparator
{
public:
  bool operator()(const CacheContext& lhs, const CacheContext& rhs) const
  {
    return lhs.getCoreId() < rhs.getCoreId();
  }
};

static const CacheContext DEFAULT_CONTEXT(0);

#endif /* CACHECONTEXT_H_ */
