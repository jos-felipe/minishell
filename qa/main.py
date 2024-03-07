#!/usr/bin/env python3

import subprocess
from modules import _00_parrot

# Exit Status
exit_status = 0

# Make clean and Make
clean = ["make", "clean", "-C", "../"]
subprocess.run(clean, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
make = ["make", "-C", "../"]
subprocess.run(make, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

# Colours
GREEN = "\033[32;1m"
RED = "\033[31;1m"
COLOR_LIMITER = "\033[0m"
colours = [GREEN, RED, COLOR_LIMITER]

# Parrot prompt
print("Parrot prompt")
exit_status = _00_parrot.parrot(colours, exit_status)
print("\n")
