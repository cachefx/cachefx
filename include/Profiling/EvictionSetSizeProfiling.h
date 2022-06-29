#ifndef EVICTIONSETSIZEPROFILING_H_
#define EVICTIONSETSIZEPROFILING_H_

#include <Profiling/Profiling.h>
#include <vector>

class MemHandle;

class EvictionAttacker;

class EvictionSetSizeProfiling : public Profiling
{
public:
  EvictionSetSizeProfiling(MMU* mmu, Cache* cache);
  virtual ~EvictionSetSizeProfiling();

  void createEvictionSet(Victim* victim, uint32_t numAddresses,
                         uint32_t maxIterations) override;

  bool createEvictionSet(Victim* victim, uint32_t numAddresses,
                         uint32_t maxIterations, MemHandle* memHandle,
                         std::vector<size_t>& evSet,
                         const bool efficiencyTest = false,
                         const uint64_t targetEvictionSetSize = TAG_NONE,
                         const double targetEvictionSetEffectiveness = 0.9)
  {
    return createEvictionSet(victim, numAddresses, maxIterations, memHandle,
                             evSet, true, efficiencyTest, targetEvictionSetSize,
                             targetEvictionSetEffectiveness);
  };

  void evaluateEvictionSet(Victim* victim, uint32_t numEvaluationRuns) override;

  ProfilingStatistic getStatistics() const override;

  uint32_t getAttackMemorySize() const { return _statAttackMemorySize; }
  uint32_t getEvictionSetSize() const { return _statEvictionSetSize; }

  friend EvictionAttacker;

private:
  double testEvictionSet(Victim* victim, MemHandle* memHandle,
                         std::vector<size_t> evSet);

private:
  bool createEvictionSet(Victim* victim, uint32_t numAddresses,
                         uint32_t maxIterations, MemHandle* memHandle,
                         std::vector<size_t>& evSet, bool output,
                         const bool efficiencyTest,
                         const uint64_t targetEvictionSetSize,
                         const double targetEvictionSetEffectiveness);
  uint32_t _statAttackMemorySize;
  uint32_t _statEvictionSetSize;
  MMU* _mmu;
  Cache* _cache;
};

#endif /* EVICTIONSETSIZEPROFILING_H_ */
