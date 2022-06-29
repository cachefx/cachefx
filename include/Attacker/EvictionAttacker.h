#ifndef __EVICTIONATTACKER_H__
#define __EVICTIONATTACKER_H__ 1

#include <fstream>
#include <unordered_set>

#include "Attacker.h"
#include "CLArgs.h"

class MMU;
class MemHandle;
class CLArgs;

class EvictionAttacker : public Attacker
{
private:
  MMU* mmu;
  const int32_t cacheSize;
  MemHandle* evSetHandle;
  int32_t evSize;
  size_t* evSet;
  int32_t noiseptr;
  int32_t bufSize;
  bool alwaysNoise;

  double testNoiseSize;

  NoiseType noiseType;
  AttackEfficacyType attackEfficacyType;

  uint64_t noiseAccesses;

  ProbeType probeType;

  unordered_set<tag_t> evTagSet;

  virtual void prime();
  virtual int32_t probe();

  ofstream* outputStats;

  virtual bool trainPostlude(const int32_t i, int32_t a, double& aSum,
                             double& aSSum, int32_t b, double& bSum,
                             double& bSSum, int32_t& count,
                             const int32_t aLastProbe = 0,
                             const int32_t bLastProbe = 0);

public:
  EvictionAttacker(MMU* mmu, int32_t cacheSize, int32_t secretRound,
                   CLArgs& args, const double testNoiseSize = 0.1,
                   const NoiseType noiseType = NT_SEPARATE);
  bool warmup(Victim* victim) { return warmup(victim, false, TAG_NONE, 0.90); }
  bool warmup(Victim* victim, const bool efficiencyTest = false,
              const uint64_t targetEvictionSetSize = TAG_NONE,
              const double targetEvictionSetEffectiveness = 0.9,
              uint64_t* const constructedEvictionSetSize = nullptr,
              double* const constructedEvictionSetProbability = nullptr);
  virtual void zeroStats()
  {
    Attacker::zeroStats();
    noiseAccesses = 0;
  };
  uint64_t getNoiseAccesses() { return noiseAccesses; };

  void setOutputStatsOfs(ofstream* outputStatsOfs)
  {
    outputStats = outputStatsOfs;
  }

  virtual ~EvictionAttacker();

  void access(){};
};

#endif // __EVICTIONATTACKER_H__
