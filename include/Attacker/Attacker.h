#ifndef __ATTACKER_H__
#define __ATTACKER_H__ 1

#include "MemHandle/MemHandle.h"
#include "Victim/Victim.h"
#include <list>
#include <vector>

class Victim;

class Attacker
{
protected:
  int32_t memAccesses;
  int32_t victimCalls;

  double aavg, acint, asavg, asd;
  double bavg, bcint, bsavg, bsd;

  double arealsum, arealssum;
  double brealsum, brealssum;
  double arealavg, arealsavg, arealsd;
  double brealavg, brealsavg, brealsd;

  double aselfevictionsum, aselfevictionssum;
  double aselfevictionavg, aselfevictionsavg, aselfevictionsd;

  double bselfevictionsum, bselfevictionssum;
  double bselfevictionavg, bselfevictionsavg, bselfevictionsd;

  int32_t warmupPeriod;

  int32_t probes;
  int32_t curRound;

  int32_t secretRound;

  int32_t giveup;

  double selfEvictionRate;
  double selfEvictions;
  int32_t lastProbe;
  uint64_t uniqueVictimLines;
  int32_t i;
  
  double numberOfProbes;

  uint64_t ABDiff;

  uint64_t areal;
  uint64_t breal;

  uint64_t correctEvictions;
  uint64_t incorrectEvictions;

  bool success;

  int32_t read(MemHandle* handle, int32_t offset,
               std::list<CacheResponse>* const cacheResp = nullptr)
  {
    memAccesses++;
    return handle->read(offset, cacheResp);
  };

  void victimCall(Victim* victim, const uint8_t* input, uint8_t* output,
                  bool aTurn)
  {
    victimCalls++;
    victim->resetAttackerAddressesEvicted();
    victim->clearCorrectEvictions();
    victim->clearIncorrectEvictions();

    victim->cipher(input, output);
    if (aTurn)
      areal = victim->getAttackerAddressesEvicted();
    else
      breal = victim->getAttackerAddressesEvicted();

    correctEvictions += victim->getCorrectEvictions();
    incorrectEvictions += victim->getIncorrectEvictions();
  };

  virtual int32_t probe() = 0;
  virtual void prime() = 0;

  void attackSetup();

  bool setStats(int32_t n, double asum, double assum, double bsum,
                double bssum);

  bool setStats(int32_t n, double asum, double assum, double bsum, double bssum,
                double aRealSum, double aRealSSum, double bRealSum,
                double bRealSSum, double aSelfEvictionSum,
                double aSelfEvictionSSum, double bSelfEvictionSum,
                double bSelfEvictionSSum);

  virtual bool trainPostlude(const int32_t i, int32_t a, double& aSum,
                             double& aSSum, int32_t b, double& bSum,
                             double& bSSum, int32_t& count,
                             const int32_t aLastProbe = 0,
                             const int32_t bLastProbe = 0) = 0;

public:
  Attacker(const int32_t secretRound, const int32_t giveup)
      : secretRound(secretRound), giveup(giveup), ABDiff(0), warmupPeriod(2)
  {
    zeroStats();
  };
  virtual bool warmup() { return true; };
  virtual bool warmup(Victim* victim) { return warmup(); };

  //:TODO: clean this up later, make this a local variable
  void train(Victim* victim, const KeyPair keys,
             std::vector<uint8_t>* overrideKeyA = nullptr,
             std::vector<uint8_t>* overrideKeyB = nullptr,
             std::vector<uint8_t>* overridePlaintext = nullptr);

  virtual void access() = 0;

  virtual void zeroStats()
  {
    memAccesses = 0;
    victimCalls = 0;
    selfEvictionRate = 0.0;
    uniqueVictimLines = 0;
    ABDiff = 0;
    areal = 0;
    breal = 0;
    correctEvictions = 0;
    incorrectEvictions = 0;
    selfEvictions = 0;
    numberOfProbes = 0;
  };
  int32_t getMemAccesses() { return memAccesses; };
  int32_t getVictimCalls() { return victimCalls; };

  //:TODO: clean this up later, make this a local variable
  void round();

  int32_t attack(const Victim* victim, const KeyPair keys);

  double getSelfEvictionRate()
  {
    return selfEvictionRate / numberOfProbes;
  };
  double getSelfEvictions()
  {
    return selfEvictions / numberOfProbes;
  };
  uint64_t getUniqueVictimLines()
  {
    return uniqueVictimLines / numberOfProbes;
  };
  double getABDiff() { return double(ABDiff); }
  uint64_t getRealEvictions()
  {
    return double(arealsum + brealsum) / numberOfProbes;
  };
  bool getSuccess() { return success; };

  double getCorrectEvictionRate()
  {
    if (correctEvictions + incorrectEvictions == 0)
      return 0;
    return double(correctEvictions) /
           double(correctEvictions + incorrectEvictions);
  };

  virtual ~Attacker(){};
};

#endif // __ATTACKER_H__
