#ifndef __ATTACK_EFFICIENCY_CONTROLLER_H__
#define __ATTACK_EFFICIENCY_CONTROLLER_H__ 1

#include <Attacker/Attacker.h>
#include <Attacker/EvictionAttacker.h>
#include <CLArgs.h>
#include <MMU/DirectMMU.h>
#include <Victim/Victim.h>
#include <memory>
#include <utility>

class AttackEfficiencyController
{
private:
  std::unique_ptr<DirectMMU> mmu;
  std::unique_ptr<Victim> victim;
  std::unique_ptr<EvictionAttacker> attacker;

  CLArgs args;

public:
  AttackEfficiencyController(CLArgs args);

  void run(int32_t nattacks);
};

#endif // __ATTACK_EFFICIENCY_CONTROLLER_H__
