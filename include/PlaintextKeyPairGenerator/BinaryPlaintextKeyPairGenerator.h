#ifndef BINARYPLAINTEXTKEYPAIRGENERATOR_H_
#define BINARYPLAINTEXTKEYPAIRGENERATOR_H_ 1

#include <cstdint>
#include <vector>

#include <PlaintextKeyPairGenerator/PlaintextKeyPairGenerator.h>
#include <Random.h>

class BinaryPlaintextKeyPairGenerator : public PlaintextKeyPairGenerator
{
protected:
  void generateKey();
  void generatePlaintext();

public:
  BinaryPlaintextKeyPairGenerator();
  virtual const std::vector<uint8_t>& getPlaintext();

  virtual ~BinaryPlaintextKeyPairGenerator(){};
};

#endif