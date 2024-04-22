#!/usr/bin/env python3

import subprocess

# Valgrind
valgrind = "valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp -q --log-file=valgrind.log"

# Colours
GREEN = "\033[32;1m"
RED = "\033[31;1m"
COLOR_LIMITER = "\033[0m"
colours = [GREEN, RED, COLOR_LIMITER]

trash = subprocess.run("make -C builtin_export", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)

# Input Samples and Outputs references:

# env_list
#1
input_data_list = ["\'export var\' \'echo $var\'"]
output_data_list = [f' ']

#2
input_data_list.append("\'export var=jojo\' \'echo $var\'")
output_data_list.append(f'jojo ')

#3
input_data_list.append("\'export var=jojo kaka\' \'echo $var\'")
output_data_list.append(f'jojo ')

#4
input_data_list.append("\'export var=\"jojo kaka\"\' \'echo $var\'")
output_data_list.append(f'jojo kaka ')

#5
input_data_list.append("\'export var=\' \'echo $var\'")
output_data_list.append(f' ')

#6
input_data_list.append("\'export =jojo\' \'echo $var\'")
output_data_list.append(f' export: not a valid identifier')

#7
input_data_list.append("\'export =\' \'echo $var\'")
output_data_list.append(f' export: not a valid identifier')

#8
input_data_list.append("\'export var1 var2=jojo\' \'echo $var1 $var2\'")
output_data_list.append(f' jojo ')

#9
input_data_list.append("\'export var1 var2=jojo =\' \'echo $var1 $var2\'")
output_data_list.append(f'jojo;\nnot a valid identifier\n')

#10
input_data_list.append("\' = export var1 var2=jojo\' \'echo $var2\'")
output_data_list.append(f'jojo;\nnot a valid identifier\n')

#11
input_data_list.append("\'export LANGUAGE=pt\' \'echo $LANGUAGE\'")
output_data_list.append(f'pt ')

#12
input_data_list.append("\'export \"\"\' \'echo $var\'")
output_data_list.append(f' export: not a valid identifier')

i = 1
for input_data, output_ref in zip(input_data_list, output_data_list):
	output = subprocess.run(f"{valgrind} ./builtin_export/unit.tester {input_data}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
	outfile_content = output.stdout
	if outfile_content == output_ref:
		print(f"{colours[0]}{i}/{len(input_data_list)}.	OK  {colours[2]}")
	else:
		print(f"{colours[1]}{i}/{len(input_data_list)}.	KO  {colours[2]}")
		
	valgrind_status = subprocess.run('./valgrind.sh', stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)

	# Check for leaks
	if (valgrind_status.stdout == '0\n'):
		print(f"{colours[0]}	MOK  {colours[2]}")
	else:
		print(f"{colours[1]}	MKO  {colours[2]}")
	i = i + 1

trash = subprocess.run("make fclean -C builtin_export", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)