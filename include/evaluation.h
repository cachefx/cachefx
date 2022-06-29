#ifndef EVALUATION_H_
#define EVALUATION_H_

#include <string>

#include <Cache/Cache.h>
#include <statistics.h>
#include <types.h>

struct EvaluationCacheCfg
{
  std::string cacheType;
  size_t nSets;
  size_t nWays;
  replAlg algorithm;
  int32_t param[4];
};

template <typename T, typename Z, typename Y>
struct ProfilingEvaluationStatistic
{
  Z evictionSetSize;
  T evictionSetTruePositiveRate;
  T evictionSR;
  T evictionSRWFlush;
  T evictionSRWEvict;
  Y attackMemorySize;
  CacheStatistics<Y> cacheStatsVictim;
  CacheStatistics<Y> cacheStatsAttacker;
  uint32_t profilingIterations;
  uint32_t evaluationIterations;
  uint32_t numStatisticalRuns;
  EvaluationCacheCfg cacheCfg;
};

#endif /* EVALUATION_H_ */
