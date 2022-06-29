#include <MMU/MMU.h>
#include <MemHandle/MemHandle.h>
#include <PlaintextKeyPairGenerator/BinaryPlaintextKeyPairGenerator.h>
#include <Victim/SingleAccessVictim.h>
#include <iostream>
#include <memory>

using namespace std;

SingleAccessVictim::SingleAccessVictim(MMU* mmu, int32_t cacheSize)
    : _mmu(mmu), _address(0)
{
  _memHandle =
      _mmu->allocate("SAVictim", cacheSize, DEFAULT_CACHE_CONTEXT_VICTIM, true);
  keyGenerator = make_unique<BinaryPlaintextKeyPairGenerator>();
}

SingleAccessVictim::SingleAccessVictim(MMU* mmu, int32_t cacheSize,
                                       bool randomAddress)
    : SingleAccessVictim::SingleAccessVictim(mmu, cacheSize)
{
  if (randomAddress)
  {
    setAddress(rand() % cacheSize);
    _memHandle->setVictimTargetAddress(_address);
  }
}
SingleAccessVictim::~SingleAccessVictim()
{
  // TODO Auto-generated destructor stub
}

void SingleAccessVictim::setAddress(address_t addr) { _address = addr; }

address_t SingleAccessVictim::getAddress() const
{
  auto allocatedSize = _memHandle->getSize();
  address_t offset = _address % allocatedSize;
  return offset;
}

int32_t SingleAccessVictim::accessAddress()
{
  auto offset = getAddress();
  // printf("Accessing address: %0lx\n", offset);
  return _memHandle->read(offset);
}

int32_t SingleAccessVictim::accessAddress(std::list<CacheResponse>& response)
{
  auto offset = getAddress();
  return _memHandle->read(offset, response);
}

/*
const MemHandle *SingleAccessVictim::getMemHandle() const {
  return _memHandle;
}
*/

void SingleAccessVictim::invalidateAddress() const
{
  auto offset = getAddress();
  _memHandle->flush(offset);
}

int32_t SingleAccessVictim::hasCollision(MemHandle* memHandle,
                                         address_t address) const
{
  return memHandle->hasCollision(address, _memHandle, _address);
}
