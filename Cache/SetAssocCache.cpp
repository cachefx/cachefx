#include <Cache/SetAssocCache.h>
#include <types.h>

const char* SetAssocCache::CACHE_TYPESTR = "set-associative";

SetAssocCache::SetAssocCache(replAlg alg, int32_t nsets, int32_t nways)
    : nsets(nsets), nways(nways)
{
  sets = new AssocCache*[nsets];

  for (int32_t i = 0; i < nsets; i++)
    sets[i] = new AssocCache(alg, nways);

  if ((uintptr_t)sets > 0)
  {
    algorithm = sets[0]->getAlgorithm();
  }
  else
  {
    algorithm = alg;
  }
}

SetAssocCache::~SetAssocCache()
{
  for (int32_t i = 0; i < nsets; i++)
    delete sets[i];

  delete[] sets;
}

void SetAssocCache::setAlgorithm(replAlg alg)
{
  for (int32_t i = 0; i < nsets; i++)
    sets[i]->setAlgorithm(alg);

  if ((uintptr_t)sets > 0)
  {
    algorithm = sets[0]->getAlgorithm();
  }
  else
  {
    algorithm = alg;
  }
}

int32_t SetAssocCache::hasCollision(tag_t cl1, const CacheContext& ctx1,
                                    tag_t cl2, const CacheContext& ctx2) const
{
  const AssocCache* assoc1 = this->getSet(cl1);
  const AssocCache* assoc2 = this->getSet(cl2);
  if (assoc1 == assoc2)
  {
    return assoc1->hasCollision(cl1, ctx1, cl2, ctx2);
  }
  return 0;
}
