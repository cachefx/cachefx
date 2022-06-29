#include <PlaintextKeyPairGenerator/BinaryPlaintextKeyPairGenerator.h>
#include <PlaintextKeyPairGenerator/PlaintextKeyPairGenerator.h>

#include <algorithm>
#include <cstdint>
#include <vector>

#include <Random.h>

using namespace std;

BinaryPlaintextKeyPairGenerator::BinaryPlaintextKeyPairGenerator()
    : PlaintextKeyPairGenerator(1, 0)
{
  generateKey();
  plaintext.push_back(0);
}

void BinaryPlaintextKeyPairGenerator::generateKey()
{
  keyA.push_back(0);
  keyB.push_back(1);

  return;
}

void BinaryPlaintextKeyPairGenerator::generatePlaintext() {}

const std::vector<uint8_t>& BinaryPlaintextKeyPairGenerator::getPlaintext()
{
  return plaintext;
}