#ifndef __DIRECTMEMHANDLE_H__
#define __DIRECTMEMHANDLE_H__ 1

#include <MMU/MMU.h>
#include <MemHandle/MemHandle.h>

#include <types.h>

class DirectMMU;

class DirectMemHandle : public MemHandle
{
private:
  DirectMMU* mmu;
  const address_t base;
  CacheContext context;
  DirectMemHandle* next;

public:
  DirectMemHandle(DirectMMU* mmu, std::string name, address_t base,
                  address_t size, CacheContext context, bool pub)
      : MemHandle(name, size, pub), mmu(mmu), base(base), context(context),
        next(NULL){};
  // virtual ~DirectMemHandle() { std::cout <<
  // "~DirectMemHandle("<<getName()<<")\n";};
  virtual ~DirectMemHandle(){};
  DirectMMU* getMMU() { return mmu; };
  address_t getBase() { return base; };

  using MemHandle::exec;
  using MemHandle::flush;
  using MemHandle::read;
  using MemHandle::write;

  virtual int32_t read(address_t offset, std::list<CacheResponse>& response)
  {
    // if (collisionCompareMemHandle && hasCollision(offset,
    // collisionCompareMemHandle, 0))
    //    tagSet.insert(translate(offset) / CACHE_LINE_SIZE);
    return mmu->getCache()->read((base + offset) / CACHE_LINE_SIZE, context,
                                 response);
  }

  virtual int32_t write(address_t offset, std::list<CacheResponse>& response)
  {
    // if (collisionCompareMemHandle && hasCollision(offset,
    // collisionCompareMemHandle, 0))
    //   tagSet.insert(translate(offset) / CACHE_LINE_SIZE);

    return mmu->getCache()->write((base + offset) / CACHE_LINE_SIZE, context,
                                  response);
  }

  virtual int32_t exec(address_t offset, std::list<CacheResponse>& response)
  {
    // if (collisionCompareMemHandle && hasCollision(offset,
    // collisionCompareMemHandle, 0))
    //   tagSet.insert(translate(offset) / CACHE_LINE_SIZE);

    return mmu->getCache()->exec((base + offset) / CACHE_LINE_SIZE, context,
                                 response);
  }

  virtual int32_t flush(address_t offset, std::list<CacheResponse>& response)
  {
    // if (collisionCompareMemHandle && hasCollision(offset,
    // collisionCompareMemHandle, 0))
    //   tagSet.insert(translate(offset) / CACHE_LINE_SIZE);

    return mmu->getCache()->evict((base + offset) / CACHE_LINE_SIZE, context,
                                  response);
  }

  CacheContext getCacheContext() const { return context; }

  address_t translate(address_t offset) const { return base + offset; }

  int32_t hasCollision(address_t offset, const MemHandle* handle,
                       address_t handleOffset)
  {
    address_t thisAddress = translate(offset);
    address_t handleAddress = handle->translate(handleOffset);
    return mmu->getCache()->hasCollision(thisAddress / CACHE_LINE_SIZE, context,
                                         handleAddress / CACHE_LINE_SIZE,
                                         handle->getCacheContext());
  }

  friend class DirectMMU;
};

#endif //__DIRECTMEMHANDLE_H__