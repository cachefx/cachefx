#ifndef STATISTICS_H_
#define STATISTICS_H_

#include <ostream>

template <typename T> class StatisticalValue
{
public:
  T max;
  T min;
  double avg;
  double var;
  T median;
  bool valid;

  friend std::ostream& operator<<(std::ostream& out, const StatisticalValue& v)
  {
    out << "(min: " << v.min << ", max: " << v.max << ", avg: " << v.avg
        << ", variance: " << v.var << ", median: " << v.median << ")";
    return out;
  };

  StatisticalValue()
      : max(0), min(0), avg(0), var(0), median(0), valid(false){};
  StatisticalValue(const StatisticalValue& v)
      : max(v.max), min(v.min), avg(v.avg), var(v.var), median(v.median),
        valid(v.valid){};
};

template <typename T = uint64_t> class CacheStatistics
{
public:
  T wrHits;
  T wrMisses;
  T wrEvictions;
  T rdHits;
  T rdMisses;
  T rdEvictions;
  T execHits;
  T execMisses;
  T execEvictions;
  T invHits;
  T invMisses;

  CacheStatistics()
      : wrHits(), wrMisses(), wrEvictions(), rdHits(), rdMisses(),
        rdEvictions(), execHits(), execMisses(), execEvictions(), invHits(),
        invMisses(){};

  CacheStatistics(T defaultValue)
      : wrHits(defaultValue), wrMisses(defaultValue), wrEvictions(defaultValue),
        rdHits(defaultValue), rdMisses(defaultValue), rdEvictions(defaultValue),
        execHits(defaultValue), execMisses(defaultValue),
        execEvictions(defaultValue), invHits(defaultValue),
        invMisses(defaultValue){};

  CacheStatistics(const CacheStatistics& stats)
      : wrHits(stats.wrHits), wrMisses(stats.wrMisses),
        wrEvictions(stats.wrEvictions), rdHits(stats.rdHits),
        rdMisses(stats.rdMisses), rdEvictions(stats.rdEvictions),
        execHits(stats.execHits), execMisses(stats.execMisses),
        execEvictions(stats.execEvictions), invHits(stats.invHits),
        invMisses(stats.invMisses){};

  friend std::ostream& operator<<(std::ostream& out,
                                  const CacheStatistics& stats)
  {
    out << "Read Hits: " << stats.rdHits << std::endl;
    out << "Read Misses: " << stats.rdMisses << std::endl;
    out << "Read Evictions: " << stats.rdEvictions << std::endl;
    out << "Write Hits: " << stats.wrHits << std::endl;
    out << "Write Misses: " << stats.wrMisses << std::endl;
    out << "Write Evictions: " << stats.wrEvictions << std::endl;
    out << "Exec Hits: " << stats.execHits << std::endl;
    out << "Exec Misses: " << stats.execMisses << std::endl;
    out << "Exec Evictions: " << stats.execEvictions << std::endl;
    out << "Invalidation Hits: " << stats.invHits << std::endl;
    out << "Invalidation Misses: " << stats.invMisses << std::endl;
    return out;
  };
};

#endif /* STATISTICS_H_ */
