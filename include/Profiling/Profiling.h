#ifndef PROFILING_H_
#define PROFILING_H_

#include "Victim/SingleAccessVictim.h"
#include <Victim/Victim.h>

struct ProfilingStatistic
{
  uint32_t numProfilingRuns;
  uint32_t numEvaluationRuns;
  uint32_t numEvaluationMisses;
  uint32_t numEvaluationMissesWFlush;
  uint32_t numEvaluationMissesWEvict;
  uint32_t numEvaluationTruePositives;
  uint32_t numEvaluationFalsePositives;
  uint64_t attackMemorySize;
};

class Profiling
{
public:
  Profiling(){};
  virtual ~Profiling(){};
  virtual void createEvictionSet(Victim* v, uint32_t numAddresses,
                                 uint32_t maxIterations) = 0;
  virtual void evaluateEvictionSet(Victim* victim,
                                   uint32_t numEvaluationRuns) = 0;
  virtual ProfilingStatistic getStatistics() const = 0;
};

#endif /* PROFILING_H_ */
