import sys;
import os;
import datetime;
import queue;
import threading;
import subprocess;
import pandas;

NUM_TREADS = 8

def findConfigsAndSetupResults(configPath, resultsPath):
  configs = []
  if os.path.isdir(resultsPath) == False:
    os.mkdir(resultsPath)

  files = os.listdir(configPath)
  for file in files:
    configFilePath = os.path.join(configPath, file)
    if os.path.isdir(configFilePath):
      subDirResults = os.path.join(resultsPath, file)
      configs += findConfigsAndSetupResults(configFilePath, subDirResults)
    else:
      fileWOExt = os.path.splitext(file)[0]
      profilingResultsFile = "profiling_" + fileWOExt + ".csv"
      entropyResultsFile = "entropy_" + fileWOExt + ".csv"
      profilingResultsPath = os.path.join(resultsPath, profilingResultsFile)
      entropyResultsPath = os.path.join(resultsPath, entropyResultsFile)
      attackerAESEvictionResultsPath = os.path.join(resultsPath, "attacker_AES_Eviction_" + fileWOExt + ".csv")
      attackerSquareMultEvictionResultsPath = os.path.join(resultsPath, "attacker_SquareMult_Eviction_" + fileWOExt + ".csv")
      attackerAESOccupancyResultsPath = os.path.join(resultsPath, "attacker_AES_Occupancy_" + fileWOExt + ".csv")
      attackerSquareMultOccupancyResultsPath = os.path.join(resultsPath, "attacker_SquareMult_Occupancy_" + fileWOExt + ".csv")
      bestEvictionSetSizeResultsPath = os.path.join(resultsPath, "best_eviction_set_size_" + fileWOExt + ".csv")
      
      # configs.append([configFilePath, profilingResultsPath, entropyResultsPath])
      configs.append({'configFilePath': configFilePath, 'profilingResultsPath': profilingResultsPath,
                      'entropyResultsPath': entropyResultsPath, 'attackerAESEvictionResultsPath': attackerAESEvictionResultsPath,
                      'attackerSquareMultEvictionResultsPath': attackerSquareMultEvictionResultsPath, 'attackerAESOccupancyResultsPath': attackerAESOccupancyResultsPath,
                      'attackerSquareMultOccupancyResultsPath': attackerSquareMultOccupancyResultsPath, 'bestEvictionSetSizeResultsPath': bestEvictionSetSizeResultsPath})

  return configs

def cacheFxWorkerThread():
  while True:
    cfg = cacheFxConfigQueue.get()
    if cfg is None:  # EOF?
      return
    #print(cfg)
    subprocess.run([exePath, "--config", cfg['configFilePath'], "--measure", "entropy", "--output", cfg['entropyResultsPath']])
    subprocess.run([exePath, "--config", cfg['configFilePath'], "--measure", "profiling", "--output", cfg['profilingResultsPath']])
    
    subprocess.call([exePath, "--config", cfg['configFilePath'], "--measure", "attacker", "-v", "AES", "-a", "eviction"], stdout=open(cfg['attackerAESEvictionResultsPath'], "w"))
    subprocess.call([exePath, "--config", cfg['configFilePath'], "--measure", "attacker", "-v", "SquareMult", "-a", "eviction"], stdout=open(cfg['attackerSquareMultEvictionResultsPath'], "w"))
    subprocess.call([exePath, "--config", cfg['configFilePath'], "--measure", "attacker", "-v", "AES", "-a", "occupancy"], stdout=open(cfg['attackerAESOccupancyResultsPath'], "w"))
    subprocess.call([exePath, "--config", cfg['configFilePath'], "--measure", "attacker", "-v", "SquareMult", "-a", "occupancy"], stdout=open(cfg['attackerSquareMultOccupancyResultsPath'], "w"))
    
    subprocess.run([exePath, "--config", cfg['configFilePath'], "--measure", "efficiency", "-v", "AES", "--output", cfg['bestEvictionSetSizeResultsPath'], "-i", "200", "-l", "0", "-e", "1200", "-y", "0", "-z", "0", "-n", "10", "-f", "always", "-g", "20000", "-t", "heatmap"])

#workingDir = os.getcwd();
scriptDir = sys.path[0]
configPath = os.path.join(scriptDir, "/workdir/sample_configs_small")
exePath = os.path.join(scriptDir, "/workdir/cachefx")
resultsPath = os.path.join(scriptDir, "/workdir/results")

if os.path.isdir(configPath) == False:
  print("Error: no configurations available!")
  sys.exit(1)

if os.path.isdir(resultsPath) == False:
  os.mkdir(resultsPath)

runTime = datetime.datetime.now()

resultsPath = os.path.join(resultsPath, str(runTime)) #runTime.strftime("%d-%b-%Y (%H:%M:%S.%f)")

cacheFxConfigs = findConfigsAndSetupResults(configPath, resultsPath)
cacheFxConfigQueue = queue.Queue()
for cfg in cacheFxConfigs:
  cacheFxConfigQueue.put(cfg)
#cacheFxConfigQueue.put(cacheFxConfigs[1])
#cacheFxConfigQueue.put(cacheFxConfigs[2])

cacheFxThreads = [ threading.Thread(target=cacheFxWorkerThread) for _i in range(NUM_TREADS) ]

for thread in cacheFxThreads:
  thread.start()
  cacheFxConfigQueue.put(None)  # one EOF marker for each thread

for thread in cacheFxThreads:
  thread.join()
