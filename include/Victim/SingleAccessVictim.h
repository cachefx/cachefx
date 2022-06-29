#ifndef SINGLEACCESSVICTIM_H_
#define SINGLEACCESSVICTIM_H_

#include <Cache/Cache.h>
#include <MemHandle/MemHandle.h>
#include <Victim/Victim.h>

class MMU;
// class MemHandle;

class SingleAccessVictim : public Victim
{
public:
  SingleAccessVictim(MMU* mmu, int32_t cacheSize);
  SingleAccessVictim(MMU* mmu, int32_t cacheSize, bool randomAddress);

  virtual ~SingleAccessVictim();

  void setAddress(address_t addr);
  address_t getAddress() const;
  void invalidateAddress() const;
  // const MemHandle *getMemHandle() const;

  int32_t accessAddress();
  int32_t accessAddress(std::list<CacheResponse>& response);

  int32_t hasCollision(MemHandle* memHandle, address_t address) const;

  // These are required for real victims...
  int32_t getKeySize(void) const { return 1; };
  // ABChoice *genKeyPair() const {return NULL; };
  int32_t getInputSize(void) const { return 1; };
  int32_t getOutputSize(void) const { return 1; };
  void setKey(const uint8_t* secret){};
  uint8_t getSecret() { return 0; }
  void cipher(const uint8_t* input, uint8_t* output) { accessAddress(); };

  virtual uint64_t getUniqueVictimTags()
  {
    return _memHandle->getUniqueTags();
  };
  virtual void clearUniqueVictimTags() { _memHandle->clearUniqueTags(); };

  virtual void setAttackerEvictionSet(std::unordered_set<tag_t>* evSet)
  {
    _memHandle->setEvSet(evSet);
  };
  virtual uint64_t getAttackerAddressesEvicted() const
  {
    return _memHandle->getAttackerAddressesEvicted();
  };
  virtual void resetAttackerAddressesEvicted()
  {
    _memHandle->resetAttackerAddressesEvicted();
  };

  virtual uint64_t getCorrectEvictions()
  {
    return _memHandle->getCorrectEvictions();
  };
  virtual void clearCorrectEvictions() { _memHandle->clearCorrectEvictions(); };

  virtual uint64_t getIncorrectEvictions()
  {
    return _memHandle->getIncorrectEvictions();
  };
  virtual void clearIncorrectEvictions()
  {
    _memHandle->clearIncorrectEvictions();
  };

private:
  MemHandle* _memHandle;
  MMU* _mmu;
  address_t _address;
};

#endif /* SINGLEACCESSVICTIM_H_ */
