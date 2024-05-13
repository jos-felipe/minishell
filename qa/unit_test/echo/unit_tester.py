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
stdin_list = ["\'echo\'"]
returned_instance = subprocess.run("bash -c 'echo'", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
stdout_list = [returned_instance.stdout]
stderr_list = [returned_instance.stderr]
returncode_list = [returned_instance.returncode]

#2
test_description_list.append(" - single word")
stdin_list.append("\'export var=jojo\' \'echo $var\'")
stdout_list.append(f'jojo ')
stderr_list.append(f'')
returncode_list.append(0)

test_description_list.append(" - multiple words")
stdin_list.append("\'export var=jojo kaka\' \'echo $var\'")
stdout_list.append(f'jojo ')
stderr_list.append(f'')
returncode_list.append(0)

test_description_list.append(" - null value variant")
stdin_list.append("\'export var=\' \'echo $var\'")
stdout_list.append(f' ')
stderr_list.append(f'')
returncode_list.append(0)

test_description_list.append(" - invalid identifier with value")
stdin_list.append("\'export =jojo\'")
stdout_list.append(f'')
stderr_list.append(f'export: not a valid identifier\n')
returncode_list.append(1)

test_description_list.append(" - invalid identifier without value")
stdin_list.append("\'export =\'")
stdout_list.append(f'')
stderr_list.append(f'export: not a valid identifier\n')
returncode_list.append(1)

test_description_list.append(" - multiple variables")
stdin_list.append("\'export var1=kaka var2=jojo\' \'echo $var1 $var2\'")
stdout_list.append(f'kaka jojo ')
stderr_list.append(f'')
returncode_list.append(0)

test_description_list.append(" - multiple variables plus invalid identifier")
stdin_list.append("\'export var1 var2=jojo =\' \'echo $var1 $var2\'")
stdout_list.append(f' jojo ')
stderr_list.append(f'export: not a valid identifier\n')
returncode_list.append(1)

test_description_list.append(" - update variable content")
stdin_list.append("\'export LANG=pt\' \'echo $LANG\'")
stdout_list.append(f'pt ')
stderr_list.append(f'')
returncode_list.append(0)

test_description_list.append(" - don't update if null address")
stdin_list.append("\'export LANG\' \'echo $LANG\'")
stdout_list.append(f'en_US.UTF-8 ')
stderr_list.append(f'')
returncode_list.append(0)

test_description_list.append(" - update if null value")
stdin_list.append("\'export LANG=\' \'echo $LANG\'")
stdout_list.append(f' ')
stderr_list.append(f'')
returncode_list.append(0)

test_description_list.append(" - assign value using expansion")
stdin_list.append("\'export var=$LANG\' \'echo $var\'")
stdout_list.append(f'en_US.UTF-8 ')
stderr_list.append(f'')
returncode_list.append(0)

test_description_list.append(" - assign value using invalid expansion")
stdin_list.append("\'export var=$affsdf\' \'echo $var\'")
stdout_list.append(f' ')
stderr_list.append(f'')
returncode_list.append(0)

test_description_list.append(" - variable name starting with number")
stdin_list.append("\'export 1var=jojo\' \'echo $1var\'")
stdout_list.append(f' ')
stderr_list.append(f'export: not a valid identifier\n')
returncode_list.append(1)

test_description_list.append(" - variable name ending with number")
stdin_list.append("\'export var1=jojo\' \'echo $var1\'")
stdout_list.append(f'jojo ')
stderr_list.append(f'')
returncode_list.append(0)

test_description_list.append(" - export with no options")
stdin_list.append("\'export SHLVL=2\' \'export\'")
export_status = subprocess.run('bash -c "export"', stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
stdout_list.append(export_status.stdout)
stderr_list.append(f'')
returncode_list.append(0)


i = 1
for input_data, output_ref, err_ref in zip(stdin_list, stdout_list, stderr_list):
	output = subprocess.run(f"./{unit}/unit.tester {input_data}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
	outfile_content = output.stdout
	errfile_content = output.stderr
	print(f"{colours[3]}{i}/{len(stdin_list)}{test_description_list[i-1]}{colours[0]}")
	if outfile_content == output_ref and errfile_content == err_ref and output.returncode == returncode_list[i-1]:
		print(f"{colours[2]}	OK{colours[0]}")
	else:
		print(f"{colours[1]}	KO{colours[0]}")
		if outfile_content != output_ref:
			print(f"{colours[4]}stdout Diff{colours[0]}")
			print(string_difference(output_ref, outfile_content))
		if errfile_content != err_ref:
			print(f"{colours[4]}stderr Diff{colours[0]}")
			print(string_difference(err_ref, errfile_content))
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
