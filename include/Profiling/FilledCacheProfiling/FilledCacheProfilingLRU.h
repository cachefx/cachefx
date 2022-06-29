#ifndef FILLEDCACHEPROFILINGLRU_H_
#define FILLEDCACHEPROFILINGLRU_H_

#include "FilledCacheProfiling.h"

class FilledCacheProfilingLRU : public FilledCacheProfiling
{
public:
  FilledCacheProfilingLRU(MMU* mmu, size_t cacheSize);
  FilledCacheProfilingLRU(MMU* mmu, size_t cacheSize, bool plru);
  virtual ~FilledCacheProfilingLRU();

  void createEvictionSet(Victim* victim, uint32_t numAddresses,
                         uint32_t maxIterations) override;

protected:
  void selectCandidates(std::vector<char>& candidateSet);
  void selectCandidatesPLRU(std::vector<char>& candidateSet);
  int32_t pruneCandidateSet(std::vector<char>& candidateSet,
                            address_t startAddress);
  void probeCache(std::vector<char> candidateSet,
                  std::vector<int32_t>& candidateCount, address_t startAddress);
  void probeCacheFwd(std::vector<char> candidateSet,
                     std::vector<int32_t>& candidateCount,
                     address_t startAddress);

  bool _plru;
};

#endif /* FILLEDCACHEPROFILINGLRU_H_ */
