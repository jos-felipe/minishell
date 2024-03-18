#!/usr/bin/env python3

import subprocess
from debug_modules import _05_sintax_analysis

# Exit Status
exit_status = 0

# Make clean and Make
clean = ["make", "clean", "-C", "../"]
subprocess.run(clean, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
make = ["make", "-C", "../"]
subprocess.run(make, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

# Command
command = "valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=../readline.supp -q ../minishell"

# Colours
GREEN = "\033[32;1m"
RED = "\033[31;1m"
COLOR_LIMITER = "\033[0m"
colours = [GREEN, RED, COLOR_LIMITER]

# Sintax Analisys
print("Sintax Analisys")
exit_status = _05_sintax_analysis.sintax_analysis(command, colours, exit_status)
print("\n")

subprocess.run(clean, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

if exit_status == 0:
	print("🎉🎊🌟✨👏🎈🎈👏👏👏🎈🎈👏🌟✨🎉🎊\n")
else:
	print("🛑 ⚠️ ❌ 💥")
exit(exit_status)
