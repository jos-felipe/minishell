#!/usr/bin/env python3

# https://www.gnu.org/savannah-checkouts/gnu/bash/manual/html_node/Bash-Builtins.html#index-echo

unit = 'echo'

import subprocess
import difflib

def string_difference(s1, s2):
	differ = difflib.Differ()
	diff = differ.compare(s1.splitlines(), s2.splitlines())
	for line in diff:
		if line.startswith('+') or line.startswith('-'):
			print(line)

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

# Check for stdout, stderr and exit status
i = 1
test_pass = True
for input_data, output_ref, err_ref in zip(stdin_list, stdout_list, stderr_list):
	output = subprocess.run(f"./{unit}/unit.tester {input_data}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
	outfile_content = output.stdout
	errfile_content = output.stderr
	print(f"{colours[3]}{i}/{len(stdin_list)}{test_description_list[i-1]}{colours[0]}")

	diff_returned = subprocess.run(f"diff <(echo {output_ref}) <(echo {outfile_content})", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
	if diff_returned.stdout != '':
		test_pass = False
		print(f"{colours[4]}stdout diff{colours[0]}")
		print(diff_returned.stdout)

	if outfile_content == output_ref and errfile_content == err_ref and output.returncode == returncode_list[i-1]:
		print(f"{colours[2]}	OK{colours[0]}")
	else:
		print(f"{colours[1]}	KO{colours[0]}")
		if outfile_content != output_ref:
			print(f"{colours[4]}stdout diff{colours[0]}")
			diff_returned = subprocess.run(f"diff <(echo {output_ref}) <(echo {outfile_content})", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
			print(diff_returned.stdout)
		if errfile_content != err_ref:
			print(f"{colours[4]}stderr diff{colours[0]}")
			diff_returned = subprocess.run(f"diff <(echo {err_ref}) <(echo {errfile_content})", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
			print(diff_returned.stdout)
		if output.returncode != returncode_list[i-1]:
			print(f"{colours[4]}exit status{colours[0]}")
			print(f"Expected: {returncode_list[i-1]}")
			print(f"Got: {output.returncode}")
	
	# Check for leaks
	subprocess.run(f"{valgrind} ./{unit}/unit.tester {input_data}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
	valgrind_status = subprocess.run(f"./valgrind.sh", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
	if (valgrind_status.stdout == '0\n'):
		print(f"{colours[2]}	MOK{colours[0]}")
	else:
		print(f"{colours[1]}	MKO{colours[0]}")
	i = i + 1

trash = subprocess.run(f"make fclean -C {unit}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
