#ifndef FILLEDCACHEPROFILINGPROBABILISTIC_H_
#define FILLEDCACHEPROFILINGPROBABILISTIC_H_

#include "FilledCacheProfiling.h"

class FilledCacheProfilingProbabilistic : public FilledCacheProfiling
{
public:
  FilledCacheProfilingProbabilistic(MMU* mmu, size_t cacheSize,
                                    bool profiledThreshold);
  virtual ~FilledCacheProfilingProbabilistic();

  virtual void createEvictionSet(Victim* victim, uint32_t numAddresses,
                                 uint32_t maxIterations);

protected:
  void probeCache(std::vector<char> candidateSet,
                  std::vector<int32_t>& candidateCount, address_t startAddress);
  int32_t pruneCandidateSet(std::vector<char>& candidateSet,
                            address_t startAddress);
  void testCandidateCollisions(Victim* victim,
                               std::vector<bool>& candidateCollisions,
                               address_t startAddress);
  void testCandidateMisses(Victim* victim, std::vector<int32_t> candidateCount,
                           std::vector<int32_t>& candidateMisses,
                           address_t startAddress);
  double getCandidateMissThresholdSimple(std::vector<int32_t> candidateCount,
                                         std::vector<int32_t> candidateMisses);
  double
  getCandidateMissThresholdProfiled(std::vector<int32_t> candidateCount,
                                    std::vector<int32_t> candidateMisses,
                                    std::vector<bool> candidateCollisions);

protected:
  double _pruningStopCondition;
  uint32_t _numCandidateTestRuns;
  bool _profiledThreshold;
  bool _useFlush;
};

#endif /* FILLEDCACHEPROFILINGPROBABILISTIC_H_ */
