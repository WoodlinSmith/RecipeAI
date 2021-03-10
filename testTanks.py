#Script to run tanks n number of times
#Usage: python testTanks.py [runs]

import subprocess
import os
import sys

if len(sys.argv) == 1:
    print("Usage: python testTanks.py [runs]")
    exit()

csvExist = os.path.isfile('output.csv')

if csvExist:
    os.remove("output.csv")

numRuns = sys.argv[1]
numRuns = int(numRuns)


for x in range(numRuns):
    subprocess.Popen(["./mapGen", str(x)])
    subprocess.Popen(["./platform", "-fast"])


