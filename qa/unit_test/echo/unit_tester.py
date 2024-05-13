#!/usr/bin/env python3

# Unit name - the same as the directory name
unit = 'echo'

# https://www.gnu.org/savannah-checkouts/gnu/bash/manual/html_node/Bash-Builtins.html#index-echo

import subprocess

# Valgrind
valgrind = "valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp -q --log-file=valgrind.log"

# Colours
GREEN = "\033[32;1m"
RED = "\033[31;1m"
COLOR_LIMITER = "\033[0m"
CYAN = "\033[36;1;3;208m"
YELLOW = "\033[33;1m"
colours = [COLOR_LIMITER, RED, GREEN, CYAN, YELLOW]

trash = subprocess.run(f"make -C {unit}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)

# Test description, Input Samples and Outputs references:

test_description_list = [" - no opt and no str"]
stdin = "\'echo\'"
stdin_list = [stdin]
returned_instance = subprocess.run(f"bash -c {stdin}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
stdout_list = [returned_instance.stdout]
stderr_list = [returned_instance.stderr]
returncode_list = [returned_instance.returncode]

test_description_list.append(" - one str")
stdin = "\'echo 42\'"
stdin_list.append(stdin)
returned_instance = subprocess.run(f"bash -c {stdin}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
stdout_list.append(returned_instance.stdout)
stderr_list.append(returned_instance.stderr)
returncode_list.append(returned_instance.returncode)

test_description_list.append(" - two str")
stdin = "\'echo École 42\'"
stdin_list.append(stdin)
returned_instance = subprocess.run(f"bash -c {stdin}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
stdout_list.append(returned_instance.stdout)
stderr_list.append(returned_instance.stderr)
returncode_list.append(returned_instance.returncode)

test_description_list.append(" - two str with -n")
stdin = "\'echo -n École 42\'"
stdin_list.append(stdin)
returned_instance = subprocess.run(f"bash -c {stdin}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
stdout_list.append(returned_instance.stdout)
stderr_list.append(returned_instance.stderr)
returncode_list.append(returned_instance.returncode)

# Check for stdout, stderr and exit status
i = 1
for input_data, output_ref, err_ref in zip(stdin_list, stdout_list, stderr_list):
	# Open files
	outfile = open(f"{unit}/outfile", "w")
	outfile_ref = open(f"{unit}/outfile_ref", "w")
	errfile = open(f"{unit}/errfile", "w")
	errfile_ref = open(f"{unit}/errfile_ref", "w")
	
	# Run the unit
	output = subprocess.run(f"./{unit}/unit.tester {input_data}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
	outfile.write(f"{output.stdout}\n")
	outfile_ref.write(f"{output_ref}\n")
	errfile.write(f"{output.stderr}\n")
	errfile_ref.write(f"{err_ref}\n")

	# Close files
	outfile.close()
	outfile_ref.close()
	errfile.close()
	errfile_ref.close()
	
	
	print(f"{colours[3]}{i}/{len(stdin_list)}{test_description_list[i-1]}{colours[0]}")

	# Check for stdout
	diff_returned = subprocess.run(f"diff {unit}/outfile_ref {unit}/outfile", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
	if diff_returned.returncode != 0:
		print(f"{colours[1]}	KO - stdout{colours[0]}")
		print(f"{colours[4]}stdout diff{colours[0]}")
		print(f"{diff_returned.stdout}")
	else:
		print(f"{colours[2]}	OK - stdout{colours[0]}")

	# Check for stderr
	diff_returned = subprocess.run(f"diff {unit}/errfile_ref {unit}/errfile", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
	if diff_returned.returncode != 0:
		print(f"{colours[1]}	KO - stderr{colours[0]}")
		print(f"{colours[4]}stderr diff{colours[0]}")
		print(f"{diff_returned.stdout}")
	else:
		print(f"{colours[2]}	OK - stderr{colours[0]}")

	# Check for exit status
	if output.returncode != returncode_list[i-1]:
		print(f"{colours[4]}	KO - exit status{colours[0]}")
		print(f"{colours[4]}exit status diff{colours[0]}")
		print(f"Expected: {returncode_list[i-1]}")
		print(f"Got: {output.returncode}")
	else:
		print(f"{colours[2]}	OK - exit status{colours[0]}")
	
	# Check for leaks
	subprocess.run(f"{valgrind} ./{unit}/unit.tester {input_data}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
	valgrind_status = subprocess.run(f"./valgrind.sh", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
	if (valgrind_status.stdout == '0\n'):
		print(f"{colours[2]}	MOK{colours[0]}")
	else:
		print(f"{colours[1]}	MKO{colours[0]}")
	print("\n------------------------------------\n")
	i = i + 1

# Clean
subprocess.run(f"rm {unit}/outfile {unit}/outfile_ref {unit}/errfile {unit}/errfile_ref", shell=True)
trash = subprocess.run(f"make fclean -C {unit}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
