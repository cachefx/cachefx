#ifndef __BINARY_VICTIM_H__
#define __BINARY_VICTIM_H__ 1

#include <Victim/Victim.h>

class BinaryVictim : public Victim
{
private:
  uint8_t key;
  MemHandle* memHandle;
  uint64_t addressA, addressB;

public:
  BinaryVictim(MMU* mmu, CLArgs clargs);

  virtual int32_t getKeySize(void) const { return 1; };

  virtual int32_t getInputSize(void) const { return 0; };
  virtual int32_t getOutputSize(void) const { return 0; };

  virtual void setKey(const uint8_t* secret);
  virtual void cipher(const uint8_t* input, uint8_t* output);

  int32_t accessAddress();
  void invalidateAddress() const;

  int32_t hasCollision(MemHandle* memHandle, address_t address) const;

  virtual uint64_t getUniqueVictimTags();
  virtual void clearUniqueVictimTags();

  virtual void setAttackerEvictionSet(unordered_set<tag_t>* evSet);
  virtual uint64_t getAttackerAddressesEvicted() const;
  virtual void resetAttackerAddressesEvicted();

  virtual uint64_t getCorrectEvictions();
  virtual void clearCorrectEvictions();

  virtual uint64_t getIncorrectEvictions();
  virtual void clearIncorrectEvictions();

  virtual uint8_t getSecret() { return 0; };

  virtual ~BinaryVictim(){};
};

#endif // __AESVICTIM_H__
