#ifndef __CACHELINE_H__
#define __CACHELINE_H__ 1

class CacheLine
{
private:
  tag_t tag;

public:
  tag_t getTag(void);
  void setTag(tag_t line);
};

inline tag_t CacheLine::getTag(void) { return tag; }
inline void CacheLine::setTag(tag_t tag) { this->tag = tag; }

#endif //__CACHELINE_H__
