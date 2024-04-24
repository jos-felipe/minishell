#!/usr/bin/env python3

import subprocess

# Valgrind
valgrind = "valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp -q --log-file=valgrind.log"

# Colours
GREEN = "\033[32;1m"
RED = "\033[31;1m"
COLOR_LIMITER = "\033[0m"
CYAN = "\033[36;1;3;208m"
colours = [GREEN, RED, COLOR_LIMITER, CYAN]

trash = subprocess.run("make -C builtin_export", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)

# Input Samples and Outputs references:

#1
test_description_list = [" - null value"]
input_data_list = ["\'export var\' \'echo $var\'"]
output_data_list = [f' ']

#2
test_description_list.append(" - single word")
input_data_list.append("\'export var=jojo\' \'echo $var\'")
output_data_list.append(f'jojo ')

#3
test_description_list.append(" - multiple words")
input_data_list.append("\'export var=jojo kaka\' \'echo $var\'")
output_data_list.append(f'jojo ')

#4
test_description_list.append(" - null value variant")
input_data_list.append("\'export var=\' \'echo $var\'")
output_data_list.append(f' ')

#5
test_description_list.append(" - invalid identifier with value")
input_data_list.append("\'export =jojo\'")
output_data_list.append(f'export: not a valid identifier\n')

test_description_list.append(" - invalid identifier without value")
input_data_list.append("\'export =\'")
output_data_list.append(f'export: not a valid identifier\n')

test_description_list.append(" - multiple variables")
input_data_list.append("\'export var1=kaka var2=jojo\' \'echo $var1 $var2\'")
output_data_list.append(f'kaka jojo ')

test_description_list.append(" - multiple variables plus invalid identifier")
input_data_list.append("\'export var1 var2=jojo =\' \'echo $var1 $var2\'")
output_data_list.append(f'export: not a valid identifier\n jojo ')

test_description_list.append(" - update an existing variable")
input_data_list.append("\'export LANGUAGE=pt\' \'echo $LANGUAGE\'")
output_data_list.append(f'pt ')

# waiting for fix on "" tokenizier
# input_data_list.append("\'export var=\"jojo kaka\"\' \'echo $var\'")
# output_data_list.append(f'jojo kaka ')
#
# input_data_list.append("\'export \"\"\' \'echo $var\'")
# output_data_list.append(f' export: not a valid identifier')

i = 1
for input_data, output_ref in zip(input_data_list, output_data_list):
	output = subprocess.run(f"{valgrind} ./builtin_export/unit.tester {input_data}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
	outfile_content = output.stdout
	print(f"{colours[3]}{i}/{len(input_data_list)}{test_description_list[i-1]}{colours[2]}")
	if outfile_content == output_ref:
		print(f"{colours[0]}	OK{colours[2]}")
	else:
		print(f"{colours[1]}	KO{colours[2]}")
		
	valgrind_status = subprocess.run('./valgrind.sh', stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)

	# Check for leaks
	if (valgrind_status.stdout == '0\n'):
		print(f"{colours[0]}	MOK{colours[2]}")
	else:
		print(f"{colours[1]}	MKO{colours[2]}")
	i = i + 1

trash = subprocess.run("make fclean -C builtin_export", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
