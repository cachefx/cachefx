#include <PlaintextKeyPairGenerator/PlaintextKeyPairGenerator.h>
#include <PlaintextKeyPairGenerator/SquareMultPlaintextKeyPairGenerator.h>

#include <algorithm>
#include <cstdint>
#include <vector>

#include <Random.h>

using namespace std;

SquareMultPlaintextKeyPairGenerator::SquareMultPlaintextKeyPairGenerator(
    const uint64_t PkeyLength, const uint64_t Plength, const uint8_t secBit)
    : PlaintextKeyPairGenerator(PkeyLength * 2, Plength * 2), secBit(secBit)
{
  // Generate Mask.
  keyMask.resize(keyLength);
  fill(keyMask.begin(), keyMask.end(), 0);
  keyMask[(keyLength * 8 - secBit) / 8] = 1 << ((keyLength * 8 - secBit) % 8);

  generateKey();
}

void SquareMultPlaintextKeyPairGenerator::generateKey()
{
  keyA.resize(keyLength);
  keyB.resize(keyLength);
  for (uint64_t i = 0; i < keyLength; i++)
  {
    keyA[i] = Random::get()->rand() & ~keyMask[i];
    keyB[i] = Random::get()->rand() | keyMask[i];
  }

  return;
}

void SquareMultPlaintextKeyPairGenerator::generatePlaintext()
{
  plaintext.clear();

  plaintext.resize(length);
  fill(plaintext.begin(), plaintext.end(), randomUint8());

  return;
}

const std::vector<uint8_t>& SquareMultPlaintextKeyPairGenerator::getPlaintext()
{
  generatePlaintext();
  return plaintext;
}