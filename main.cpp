#include <getopt.h>
#include <iostream>
#include <map>
#include <string>
#include <unistd.h>

using namespace std;

#include <AttackEfficiencyController.h>
#include <CLArgs.h>
#include <CacheFactory/CacheFactory.h>
#include <Controller.h>
#include <EntropyLoss.h>
#include <ProfilingEvaluation.h>
#include <Victim/Victim.h>
#include <types.h>

int main(int argc, char** argv)
{
  CLArgs args;
  MeasurementType measurements = MT_INVALID;

  args.parse(argc, argv);

  // Configure cache

  CacheFactory::Instance()->setCfgFilePath(args.get_cfgFilePath());

  // Perform experiments

  switch (args.get_measurements())
  {
  case MT_ENTROPY: {
    EntropyLoss infoLoss;
    infoLoss.evaluate();
    if (args.get_fileOutput())
    {
      infoLoss.printStatistics(args.get_outputFile());
    }
    else
    {
      infoLoss.printStatistics();
    }
    break;
  }
  case MT_PROFILING: {
    ProfilingEvaluation eval;
    eval.evaluate(1);
    if (args.get_fileOutput())
    {
      eval.printStatistics(args.get_outputFile());
    }
    else
    {
      eval.printStatistics();
    }
    break;
  }
  case MT_ATTACKER: {
    if (args.get_victim() == VT_INVALID)
    {
      fprintf(stderr, "No victim specified\n");
      exit(1);
    }
    for (int32_t i = 0; i < args.get_repeats(); i++)
    {
      unique_ptr<Controller> c = make_unique<Controller>(args);
      c->run(i + 1);
    }
    break;
  }
  case MT_EFFICIENCY: {
    if (args.get_victim() == VT_INVALID)
    {
      fprintf(stderr, "No victim specified\n");
      exit(1);
    }
    unique_ptr<AttackEfficiencyController> c =
        make_unique<AttackEfficiencyController>(args);
    c->run(0);
    break;
  }
  case MT_INVALID:
  default: {
    std::cout << "Invalid or no profiling type was specified for measurements!"
              << std::endl;
    std::cout << "Profiling type can be any of the following: " << std::endl;
    std::cout << "entropy, profiling, attacker" << std::endl;
  }
  }
}
