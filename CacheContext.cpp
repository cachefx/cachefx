#include <CacheContext.h>

CacheContext::CacheContext() : _coreId(0) {}

CacheContext::CacheContext(int32_t coreId) : _coreId(coreId) {}

CacheContext::CacheContext(const CacheContext& ctx) : _coreId(ctx._coreId) {}

CacheContext::~CacheContext() {}

bool CacheContext::operator==(const CacheContext& context) const
{
  return this->_coreId == context._coreId;
}

bool CacheContext::operator!=(const CacheContext& context) const
{
  return !(*this == context);
}
