#ifndef __DIRECTMMU_H__
#define __DIRECTMMU_H__ 1

#include <Cache/Cache.h>
#include <MMU/MMU.h>
#include <MemHandle/MemHandle.h>
#include <map>
#include <memory>
#include <string>

class DirectMemHandle;

class DirectMMU : public MMU
{
private:
  address_t last;
  std::unique_ptr<Cache> cache;
  std::map<std::string, DirectMemHandle*> handles;

public:
  DirectMMU(std::unique_ptr<Cache> cache) : cache(std::move(cache))
  {
    last = 4096;
  };
  DirectMMU(std::unique_ptr<Cache> cache, bool randomize)
      : cache(std::move(cache))
  {
    if (randomize)
      last = (std::rand() % 1024) * 4096;
    else
      last = 4096;
  };
  virtual ~DirectMMU() override;
  Cache* getCache() const { return cache.get(); };

  using MMU::allocate;
  MemHandle* allocate(std::string name, address_t size, address_t align,
                      address_t fix, CacheContext context, bool pub);
  void free(MemHandle* handle);
};

#endif // __DirectMMU_H__
