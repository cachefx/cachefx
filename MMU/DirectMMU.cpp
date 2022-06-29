#include <iostream>
#include <map>
#include <string>

using namespace std;

#include <MMU/DirectMMU.h>
#include <MemHandle/DirectMemHandle.h>
#include <types.h>

DirectMMU::~DirectMMU()
{
  for (std::map<string, DirectMemHandle*>::iterator it = handles.begin();
       it != handles.end(); it++)
  {
    delete it->second;
  }
}

MemHandle* DirectMMU::allocate(string name, address_t size, address_t align,
                               address_t fix, CacheContext context, bool pub)
{
  int32_t count = handles.count(name);
  if (count != 0)
  {
    DirectMemHandle* dmh = handles[name];
    if (!pub || !dmh->isPublic())
      return NULL;
    while (dmh && dmh->context != context)
      dmh = dmh->next;
    if (dmh)
      return dmh;
    dmh = handles[name];
    DirectMemHandle* newdmh =
        new DirectMemHandle(this, name, dmh->base, size, context, true);
    newdmh->next = dmh;
    handles[name] = newdmh;
    return NULL;
  }
  address_t base = last + align - 1;
  base = (base / align) * align;
  base += fix;
  DirectMemHandle* dmh =
      new DirectMemHandle(this, name, base, size, context, pub);
  last = base + size;
  handles[name] = dmh;
  return dmh;
}

// Does not really work.
void DirectMMU::free(MemHandle* handle)
{
  string name = ((DirectMemHandle*)handle)->getName();
  DirectMemHandle* dmh = handles[name];

  if (dmh != nullptr)
  {
    handles.erase(name);
    delete handle;
  }
}
