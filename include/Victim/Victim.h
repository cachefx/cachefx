#ifndef __VICTIM_H__
#define __VICTIM_H__ 1
#include "types.h"

#include <memory>
#include <unordered_set>
#include <utility>

#include <PlaintextKeyPairGenerator/PlaintextKeyPairGenerator.h>

using KeyPair =
    std::pair<const std::vector<uint8_t>&, const std::vector<uint8_t>&>;

class ABChoice;
class MemHandle;

class Victim
{
protected:
  std::unique_ptr<PlaintextKeyPairGenerator> keyGenerator;

public:
  // static const int32_t NullVictim = 0;
  // static const int32_t AESVictim = 1;
  // static const int32_t SquareMultVictim = 2;

  virtual int32_t getKeySize(void) const = 0;
  KeyPair genKeyPair()
  {
    return KeyPair(keyGenerator->getKeyA(), keyGenerator->getKeyB());
  }

  virtual int32_t getInputSize(void) const = 0;
  virtual int32_t getOutputSize(void) const = 0;

  const std::vector<uint8_t>& getRandomInput() const
  {
    return keyGenerator->getPlaintext();
  }

  virtual void setKey(const uint8_t* secret) = 0;
  virtual uint8_t getSecret() = 0;
  virtual void cipher(const uint8_t* input, uint8_t* output) = 0;

  virtual void invalidateAddress() const = 0;
  virtual int32_t accessAddress() = 0;
  virtual int32_t hasCollision(MemHandle* memHandle,
                               address_t address) const = 0;

  virtual uint64_t getUniqueVictimTags() = 0;
  virtual void clearUniqueVictimTags() = 0;

  virtual void setAttackerEvictionSet(std::unordered_set<tag_t>* evSet) = 0;
  virtual uint64_t getAttackerAddressesEvicted() const = 0;
  virtual void resetAttackerAddressesEvicted() = 0;

  virtual uint64_t getCorrectEvictions() = 0;
  virtual void clearCorrectEvictions() = 0;

  virtual uint64_t getIncorrectEvictions() = 0;
  virtual void clearIncorrectEvictions() = 0;

  virtual ~Victim(){};
};

#endif // __VICTIM_H__
