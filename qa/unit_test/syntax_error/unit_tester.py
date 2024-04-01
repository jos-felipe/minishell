#!/usr/bin/env python3

import subprocess

# Valgrind
valgrind = "valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp -q --log-file=valgrind.log"

# Colours
GREEN = "\033[32;1m"
RED = "\033[31;1m"
COLOR_LIMITER = "\033[0m"
colours = [GREEN, RED, COLOR_LIMITER]

trash = subprocess.run("make", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)

# Input Samples:
input_data_list = ["\"a b | c d\""]
input_data_list.append("\"a b|c d\"")
input_data_list.append("\"a b |\"")
input_data_list.append("\"a b|\"")
input_data_list.append("\"| c d\"")
input_data_list.append("\"|c d\"")
input_data_list.append("\"|\"")
input_data_list.append("\"  |  \"")

# Outputs references:
output_data_list = [f'']
output_data_list.append(f'')
output_data_list.append(f'bash: syntax error near unexpected token `|\'\n')
output_data_list.append(f'bash: syntax error near unexpected token `|\'\n')
output_data_list.append(f'bash: syntax error near unexpected token `|\'\n')
output_data_list.append(f'bash: syntax error near unexpected token `|\'\n')
output_data_list.append(f'bash: syntax error near unexpected token `|\'\n')
output_data_list.append(f'bash: syntax error near unexpected token `|\'\n')

i = 1
for input_data, output_ref in zip(input_data_list, output_data_list):
	output = subprocess.run(f"{valgrind} ./syntax_error {input_data}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
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

trash = subprocess.run("make fclean", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)