#ifndef FILLEDCACHEPROFILINGGROUPELIM_H_
#define FILLEDCACHEPROFILINGGROUPELIM_H_

#include "FilledCacheProfiling.h"
#include <Cache/Cache.h>

class FilledCacheProfilingGroupElim : public FilledCacheProfiling
{
public:
  FilledCacheProfilingGroupElim(MMU* mmu, Cache* cache);
  FilledCacheProfilingGroupElim(MMU* mmu, Cache* cache, bool plru);
  virtual ~FilledCacheProfilingGroupElim();

  void createEvictionSet(Victim* victim, uint32_t numAddresses,
                         uint32_t maxIterations) override;

protected:
  size_t selectCandidates(std::vector<char>& candidateSet);
  size_t selectCandidatesPLRU(std::vector<char>& candidateSet);
  bool hasConflict(Victim* victim, std::vector<char>& candidateSet,
                   address_t startAddress);
  size_t pruneCandidateSet(std::vector<char>& candidateSet,
                           std::vector<int32_t>& candidateSetGroupIndx,
                           size_t pruneGroupIndx);
  void unpruneCandidateSet(std::vector<char>& candidateSet,
                           std::vector<int32_t>& candidateSetGroupIndx,
                           size_t pruneIndx);
  void cleanCandidateGroup(std::vector<char>& candidateSet,
                           std::vector<int32_t>& candidateSetGroupIndx,
                           size_t pruneIndx);
  void resetCandidateGroup(std::vector<int32_t>& candidateSetGroupIndx);
  void assignToGroups(std::vector<char>& candidateSet,
                      size_t candidateSetSelected,
                      std::vector<int32_t>& candidateSetGroupIndx,
                      uint32_t numOfGroups);
  double determineEvictionProbability(Victim* victim,
                                      std::vector<char>& candidateSet,
                                      address_t startAddress,
                                      int32_t totalTests);

  //  void probeCache(std::vector<char> candidateSet, std::vector<int32_t>
  //  &candidateCount, address_t startAddress); void
  //  probeCacheFwd(std::vector<char> candidateSet, std::vector<int32_t>
  //  &candidateCount, address_t startAddress);

  bool _plru;
  Cache* _cache;
};

#endif /* FILLEDCACHEPROFILINGGROUPELIM_H_ */
