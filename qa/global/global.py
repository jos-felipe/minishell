#!/usr/bin/env python3

import subprocess
import os

# Colours
GREEN = "\033[32;1m"
RED = "\033[31;1m"
COLOR_LIMITER = "\033[0m"
colours = [GREEN, RED, COLOR_LIMITER]

# Remove log file
subprocess.run("rm log_file", shell=True)

user = os.environ['USER']

# INPUT REFERENCE LIST
input_list = ["echo 42"] #1
input_list.append("ERR") #2

# OUTPUT REFERENCE LIST
output_ref_list = ["42\n"] #1
output_ref_list.append("minishell: ERR: command not found\n") #2

# OUTPUT EXIT CODE LIST
output_exit_code = ["0\n"] #1
output_exit_code.append("127\n") #2

i = 1
for command, reference, reference_exit_code in zip(input_list, output_ref_list, output_exit_code):
    command_exit_code = "\necho $?"
    with open("file", "w") as file:
        file.write(command + command_exit_code)
    with open("ref_file", "w") as ref_file:
        ref_file.write(reference)
    with open("status_ref_file", "w") as status_ref_file:
        status_ref_file.write(reference_exit_code)
    output = subprocess.run("./script.sh", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)

    if (output.stdout == '0\n'):
        print(f"{colours[0]}{i}/{len(input_list)}.\n	OK  {colours[2]}")
    else:
        print(f"{colours[1]}{i}/{len(input_list)}.\n	KO  {colours[2]}")
    valgrind_status = subprocess.run('./valgrind.sh', stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
    if (valgrind_status.stdout == '0\n'):
        print(f"{colours[0]}	MOK  {colours[2]}")
    else:
        print(f"{colours[1]}	MKO  {colours[2]}")
    status = subprocess.run("./status.sh", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
    if (status.stdout == '0\n'):
        print(f"{colours[0]}	EOK  {colours[2]}")
    else:
        print(f"{colours[1]}	EKO  {colours[2]}")
    with open("result", "r") as result_file:
        result_command = result_file.read()
    with open("status_result", "r") as status_result_file:
        status_result = status_result_file.readlines()[-1]
    with open("log_file", "a") as log_file:
        log_file.write(f"{i}.\ncommand:\n{command}\nexpected output:\n{reference}\noutput received:\n{result_command}\nexpected status: {reference_exit_code}\nstatus received: {status_result}\n\n")
    i = i + 1
file_paths = [" ", "filename", "fdasdfsa", "file", "infile1", "infile2", "outfile1", "tudo", "outfile3", "ref_file", "outfile", "result", "status_file", "status_outfile", "status_ref_file", "status_result", "valgrind.log"]
rm_command = ["rm", "-f"] + file_paths
subprocess.run(rm_command)