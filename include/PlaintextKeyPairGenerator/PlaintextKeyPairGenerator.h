#ifndef PLAINTEXTKEYPAIRGENERATOR_H_
#define PLAINTEXTKEYPAIRGENERATOR_H_ 1

#include <random>
#include <utility>
#include <vector>

class PlaintextKeyPairGenerator
{
protected:
  std::vector<uint8_t> keyA;
  std::vector<uint8_t> keyB;

  std::vector<uint8_t> plaintext;

  uint64_t keyLength;
  uint64_t length;

  virtual void generateKey() = 0;
  virtual void generatePlaintext() = 0;

public:
  PlaintextKeyPairGenerator(const uint64_t keyLength, const uint64_t length)
      : keyLength(keyLength), length(length)
  {
  }
  const std::vector<uint8_t>& getKeyA() const { return keyA; }
  const std::vector<uint8_t>& getKeyB() const { return keyB; }

  virtual const std::vector<uint8_t>& getPlaintext() = 0;

  uint64_t getKeyLength() const { return keyLength; }
  uint64_t getLength() const { return length; }

  virtual ~PlaintextKeyPairGenerator(){};
};

#endif