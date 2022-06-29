#ifndef __SQUAREMULTATTACKER_H__
#define __SQUAREMULTATTACKER_H__ 1

#include "Attacker.h"

class MMU;
class MemHandle;

class SquareMultAttacker : public Attacker
{
private:
  MMU* mmu;
  const int32_t cacheSize;
  MemHandle* evictionSet;
  int32_t secbyte;

  int32_t roundcount;
  int32_t probes[8];
  int32_t threshold;

  void setup();
  void prime();
  int32_t probe();

public:
  SquareMultAttacker(MMU* mmu, int32_t cacheSize, int32_t secbyte);
  void train(Victim* victim, const KeyPair keys);
  int32_t attack(const Victim* victim, const KeyPair keys);
  void round();
  void access(){};
};

#endif // __SQUAREMULTATTACKER_H__
