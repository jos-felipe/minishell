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
input_data_list = ["\"echo\""]
input_data_list.append("\"echo -n Mephis\"")
input_data_list.append("\"echo -n Mephis > outfile\"")
input_data_list.append("\"echo -n Mephis >> outfile\"")
input_data_list.append("\"cat -e < infile\"")
input_data_list.append("\"> outfile cat -e < infile\"")
input_data_list.append("\"> outfile\"")
input_data_list.append("\">outfile\"")
input_data_list.append("\"< infile\"")
input_data_list.append("\"<infile\"")
input_data_list.append("\"<< echo\"")
input_data_list.append("\"cat -n infile | grep 'pattern'\"")
input_data_list.append("\"echo 'Mephis e Fausto'\"")
input_data_list.append("'echo \"Mephis e Fausto\"'")

# Outputs references:
output_data_list = [f'echo;']
output_data_list.append(f'echo;-n;Mephis;')
output_data_list.append(f'echo;-n;Mephis;>;outfile;')
output_data_list.append(f'echo;-n;Mephis;>>;outfile;')
output_data_list.append(f'cat;-e;<;infile;')
output_data_list.append(f'>;outfile;cat;-e;<;infile;')
output_data_list.append(f'>;outfile;')
output_data_list.append(f'>;outfile;')
output_data_list.append(f'<;infile;')
output_data_list.append(f'<;infile;')
output_data_list.append(f'<<;echo;')
output_data_list.append(f'cat;-n;infile;|;grep;\'pattern\';')
output_data_list.append(f"echo;'Mephis e Fausto';")
output_data_list.append(f'echo;"Mephis e Fausto";')

i = 1
for input_data, output_ref in zip(input_data_list, output_data_list):
	output = subprocess.run(f"{valgrind} ./tokenizer {input_data}", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
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