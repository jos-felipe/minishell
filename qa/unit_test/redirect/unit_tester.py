#!/usr/bin/env python3

import subprocess

# Program name
name = "redirect"

# Valgrind
valgrind = "valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp -q --log-file=valgrind.log"

# Colours
GREEN = "\033[32;1m"
RED = "\033[31;1m"
COLOR_LIMITER = "\033[0m"
colours = [GREEN, RED, COLOR_LIMITER]

trash = subprocess.run(f"make -C {name}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
trash = subprocess.run(f"touch in1 in2", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)


# Input Samples:
input_data_list = ["\'echo melvin > out\'"]
output_data_list = [f'0|4\n']

input_data_list.append("\'echo melvin > out1 > out2\'")
output_data_list.append(f'0|5\n')

input_data_list.append("\'> out\'")
output_data_list.append(f'0|4\n')

input_data_list.append("\'< in1\'")
output_data_list.append(f'4|1\n')

input_data_list.append("\'< in1 cat > out1 > out2\'")
output_data_list.append(f'4|6\n')

input_data_list.append("\'< in1 < in2 cat > out\'")
output_data_list.append(f'5|6\n')

input_data_list.append("\'echo > out1 > out2 melvin\'")
output_data_list.append(f'0|5\n')

input_data_list.append("\'echo > out1 melvin > out2 tropical\'")
output_data_list.append(f'0|5\n')

input_data_list.append("\'echo melvin > out | < in1 cat\'")
output_data_list.append(f'0|4\n5|1\n')

i = 1

for input_data, output_ref in zip(input_data_list, output_data_list):
	output = subprocess.run(f"{valgrind} ./redirect/redirect {input_data}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
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

trash = subprocess.run(f"rm out out1 out2 in1 in2", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
trash = subprocess.run(f"make fclean -C {name}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)