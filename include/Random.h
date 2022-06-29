#ifndef __RANDOM_H__
#define __RANDOM_H__ 1

//#define NO_RDRAND

class Random
{
private:
  static Random* instance;
  uint64_t state;

  Random(uint64_t seed) : state(seed){};
  Random() : Random(rdrand())
  {
    for (int32_t i = 0; i < 100; i++)
      rand();
  };

public:
  static Random* get(void) { return instance; };

  uint64_t rand()
  {
    uint64_t x = state;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    state = x;
    return x;
  };

  void seed(uint64_t seed) { state = seed; };

  static uint64_t rdrand()
  {
#ifdef NO_RDRAND
    uint64_t a, d;
    asm volatile("rdtsc" : "=a"(a), "=d"(d));
    a = (d << 32) | a;
    return a;
#else
    uint64_t r;
    asm __volatile__("rdrand %0" : "=r"(r));
    return r;
#endif
  };
};

static inline bool randomBool() { return Random::get()->rand() & 0x01; }
static inline uint8_t randomUint8() { return Random::get()->rand() & 0xff; }

#endif //__RANDOM_H__
