#ifndef FILLEDCACHEPROFILINGSINGLEHOLD_H_
#define FILLEDCACHEPROFILINGSINGLEHOLD_H_

#include "FilledCacheProfiling.h"
#include <Cache/Cache.h>

class FilledCacheProfilingSingleHold : public FilledCacheProfiling
{
public:
  FilledCacheProfilingSingleHold(MMU* mmu, Cache* cache);
  FilledCacheProfilingSingleHold(MMU* mmu, Cache* cache, bool plru);
  virtual ~FilledCacheProfilingSingleHold();

  void createEvictionSet(Victim* victim, uint32_t numAddresses,
                         uint32_t maxIterations) override;

protected:
  size_t selectCandidates(std::vector<char>& candidateSet);
  size_t selectCandidatesPLRU(std::vector<char>& candidateSet);
  size_t pruneCandidateSet(std::vector<char>& candidateSet,
                           size_t nextPruneIndx);
  bool hasConflict(Victim* victim, std::vector<char>& candidateSet,
                   address_t startAddress);
  double determineEvictionProbability(Victim* victim,
                                      std::vector<char>& candidateSet,
                                      address_t startAddress,
                                      int32_t totalTests);
  //  void probeCache(std::vector<char> candidateSet, address_t startAddress);
  //  void probeCacheFwd(std::vector<char> candidateSet, address_t
  //  startAddress);

  bool _plru;
  Cache* _cache;
};

#endif /* FILLEDCACHEPROFILINGSINGLEHOLD_H_ */
