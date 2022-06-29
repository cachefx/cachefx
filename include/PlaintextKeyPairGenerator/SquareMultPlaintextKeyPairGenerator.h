#ifndef SQUAREMULTPLAINTEXTKEYPAIRGENERATOR_H_
#define SQUAREMULTPLAINTEXTKEYPAIRGENERATOR_H_ 1

#include <cstdint>
#include <vector>

#include <PlaintextKeyPairGenerator/PlaintextKeyPairGenerator.h>
#include <PlaintextKeyPairGenerator/SquareMultPlaintextKeyPairGenerator.h>
#include <Random.h>

class SquareMultPlaintextKeyPairGenerator : public PlaintextKeyPairGenerator
{
private:
  uint8_t secBit;
  std::vector<uint8_t> keyMask;

protected:
  void generateKey();
  void generatePlaintext();

public:
  SquareMultPlaintextKeyPairGenerator(const uint64_t keyLength,
                                      const uint64_t length,
                                      const uint8_t secBit);
  virtual const std::vector<uint8_t>& getPlaintext();

  virtual ~SquareMultPlaintextKeyPairGenerator(){};
};

#endif