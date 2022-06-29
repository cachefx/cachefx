#ifndef AESPLAINTEXTKEYPAIRGENERATOR_H_
#define AESPLAINTEXTKEYPAIRGENERATOR_H_ 1

#include <cstdint>
#include <vector>

#include <PlaintextKeyPairGenerator/PlaintextKeyPairGenerator.h>
#include <Random.h>

class AESPlaintextKeyPairGenerator : public PlaintextKeyPairGenerator
{
protected:
  void generateKey();
  void generatePlaintext();

public:
  AESPlaintextKeyPairGenerator(const uint64_t keyLength, const uint64_t length);
  virtual const std::vector<uint8_t>& getPlaintext();

  virtual ~AESPlaintextKeyPairGenerator(){};
};

#endif