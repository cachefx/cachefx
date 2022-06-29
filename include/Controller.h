#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__ 1

#include <Attacker/Attacker.h>
#include <CLArgs.h>
#include <MMU/DirectMMU.h>
#include <Victim/Victim.h>
#include <memory>
#include <utility>

class Controller
{
private:
  std::unique_ptr<DirectMMU> mmu;
  std::unique_ptr<Victim> victim;
  std::unique_ptr<Attacker> attacker;

public:
  // Controller(VictimType victimType/* Specify everything */);
  Controller(CLArgs& args);

  void run(int32_t nattacks);
};

#endif // __CONTROLLER_H__
