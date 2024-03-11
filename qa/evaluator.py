#!/usr/bin/env python3

import subprocess
from modules import _00_parrot
from modules import _01_signals
from modules import _02_launch_executable

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

# Signals
print("Signals")
exit_status = _01_signals.signals(colours, exit_status)
print("\n")

# Search and launch executable
print("Launch executable")
exit_status = _02_launch_executable.launch_executable(colours, exit_status)
print("\n")

subprocess.run(clean, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
if exit_status == 0:
	print("🎉🎊🌟✨👏🎈🎈👏👏👏🎈🎈👏🌟✨🎉🎊\n")
	
exit(exit_status)
