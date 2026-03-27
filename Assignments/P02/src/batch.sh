#!/usr/bin/env python3

import subprocess
import os,sys
import json
#from path import Path

dir = os.getcwd()
print(dir)
#sys.exit()

workloads = ["A", "B", "C", "D"]
sizes = [1000, 5000, 10000, 20000]

for w in workloads:
    for n in sizes:
        outfile = f"workloads/workload_{w}_{n}.json"

        cmd = [
            "../build/workload_generator",
            #"--json",
            "--workload", w,
            "--size", str(n),
            "--save", outfile
        ]

        print("Running:", " ".join(cmd))
        
        # try:
        #     result = subprocess.run(cmd, capture_output=True, text=True, check=True)
        #     output = result.stdout
        #     #print("Captured output:")
        #     #print(output)
        # except subprocess.CalledProcessError as e:
        #     print(f"Command failed with return code {e.returncode}")
        #     print(f"Error output: {e.stderr}")
        subprocess.run(cmd, check=True)
        # with open(outfile, "w") as f:
        #     f.write(output)