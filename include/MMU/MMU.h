#ifndef __MMU_H__
#define __MMU_H__ 1

#include <CacheContext.h>
#include <MemHandle/MemHandle.h>
#include <string>

class MMU
{
private:
  static const int32_t defaultAlign = 128;

public:
  virtual ~MMU(){};
  virtual MemHandle* allocate(std::string name, address_t size, address_t align,
                              address_t fix, CacheContext context,
                              bool pub) = 0;
  MemHandle* allocate(std::string name, address_t size, CacheContext context,
                      bool pub)
  {
    return allocate(name, size, defaultAlign, 0, context, pub);
  };
  MemHandle* allocate(std::string name, address_t size, bool pub)
  {
    return allocate(name, size, defaultAlign, 0, DEFAULT_CONTEXT, pub);
  };
  virtual void free(MemHandle* handle) = 0;

  virtual Cache* getCache() const = 0;
};

#endif // __MMU_H__
