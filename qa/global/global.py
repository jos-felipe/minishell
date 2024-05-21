#!/usr/bin/env python3

# Unit name - the same as the directory name
# unit = 'echo'

# https://www.gnu.org/savannah-checkouts/gnu/bash/manual/html_node/Bash-Builtins.html#index-echo

import subprocess

# Function to process the file content and modify it
def process_and_modify_file(filename):
    lines = []
    with open(filename, 'r+') as file:
        for line in file:
            if 'prompt >' in line:
                value = line.split("prompt >")
                if value[0] != '':
                    lines.append(value[0])
            else:
                lines.append(line)
        # lines.pop()
    return lines

# Valgrind
valgrind = "valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp -q --log-file=valgrind.log"

# Colours
GREEN = "\033[32;1m"
RED = "\033[31;1m"
COLOR_LIMITER = "\033[0m"
CYAN = "\033[36;1;3;208m"
YELLOW = "\033[33;1m"
colours = [COLOR_LIMITER, RED, GREEN, CYAN, YELLOW]

trash = subprocess.run(f"make -C ../../", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)

# Create input file
infile = open('infile', 'w')
infile.write('banana.apple.grape')
infile.close()


# Test description, Input Samples and Outputs references:

test_description_list = [" - one str"]
stdin = "echo 42"
stdin_list = [stdin]
returned_instance = subprocess.run(f"bash -c '{stdin}'", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
stdout_list = [returned_instance.stdout]
stderr_list = [returned_instance.stderr]
returncode_list = [returned_instance.returncode]

test_description_list.append(" - two str")
stdin = "echo École 42"
stdin_list.append(stdin)
returned_instance = subprocess.run(f"bash -c '{stdin}'", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
stdout_list.append(returned_instance.stdout)
stderr_list.append(returned_instance.stderr)
returncode_list.append(returned_instance.returncode)

test_description_list.append(" - two str with -n")
stdin = "echo -n École 42"
stdin_list.append(stdin)
returned_instance = subprocess.run(f"bash -c '{stdin}'", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
stdout_list.append(returned_instance.stdout)
stderr_list.append(returned_instance.stderr)
returncode_list.append(returned_instance.returncode)

test_description_list.append(" - two pipes and infile")
stdin = "cat < infile -e | tr . , | tr a-z A-Z"
stdin_list.append(stdin)
returned_instance = subprocess.run(f"bash -c '{stdin}'", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
stdout_list.append(returned_instance.stdout)
stderr_list.append(returned_instance.stderr)
returncode_list.append(returned_instance.returncode)

test_description_list.append(" - wrong command")
stdin = "cat < infile -e | trERR . , | tr a-z A-Z"
stdin_list.append(stdin)
returned_instance = subprocess.run(f"bash -c '{stdin}'", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
stdout_list.append(returned_instance.stdout)
stderr_list.append(returned_instance.stderr)
returncode_list.append(returned_instance.returncode)

test_description_list.append(" - wrong command")
stdin = "echo a | echo b | echo c"
stdin_list.append(stdin)
returned_instance = subprocess.run(f"bash -c '{stdin}'", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
stdout_list.append(returned_instance.stdout)
stderr_list.append(returned_instance.stderr)
returncode_list.append(returned_instance.returncode)

test_description_list.append(" - wrong command")
stdin = "echo a | echoERR b | echo c"
stdin_list.append(stdin)
returned_instance = subprocess.run(f"bash -c '{stdin}'", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
stdout_list.append(returned_instance.stdout)
stderr_list.append(returned_instance.stderr)
returncode_list.append(returned_instance.returncode)

test_description_list.append(" - wrong command")
stdin = "echo \'melvin ropical"
stdin_list.append(stdin)
returned_instance = subprocess.run(f"bash -c '{stdin}'", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
stdout_list.append(returned_instance.stdout)
stderr_list.append(returned_instance.stderr)
returncode_list.append(returned_instance.returncode)

test_description_list.append(" - simple expansion")
stdin = "echo $LANGUAGE"
stdin_list.append(stdin)
returned_instance = subprocess.run(f"bash -c '{stdin}'", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
stdout_list.append(returned_instance.stdout)
stderr_list.append(returned_instance.stderr)
returncode_list.append(returned_instance.returncode)

test_description_list.append(" - expand dollar sign")
stdin = "echo $?"
stdin_list.append(stdin)
returned_instance = subprocess.run(f"bash -c '{stdin}'", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
stdout_list.append(returned_instance.stdout)
stderr_list.append(returned_instance.stderr)
returncode_list.append(returned_instance.returncode)

test_description_list.append(" - expand dollar sign plus variable")
stdin = "echo $?LANGUAGE"
stdin_list.append(stdin)
returned_instance = subprocess.run(f"bash -c '{stdin}'", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
stdout_list.append(returned_instance.stdout)
stderr_list.append(returned_instance.stderr)
returncode_list.append(returned_instance.returncode)

test_description_list.append(" - expand with invalid in the middle")
stdin = "echo $abc^def"
stdin_list.append(stdin)
returned_instance = subprocess.run(f"bash -c '{stdin}'", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
stdout_list.append(returned_instance.stdout)
stderr_list.append(returned_instance.stderr)
returncode_list.append(returned_instance.returncode)

test_description_list.append(" - expand with invalid in the front")
stdin = "echo $^abc"
stdin_list.append(stdin)
returned_instance = subprocess.run(f"bash -c '{stdin}'", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
stdout_list.append(returned_instance.stdout)
stderr_list.append(returned_instance.stderr)
returncode_list.append(returned_instance.returncode)

test_description_list.append(" - simple expand with invalid in the middle")
stdin = "echo $LANGUAGE^abc"
stdin_list.append(stdin)
returned_instance = subprocess.run(f"bash -c '{stdin}'", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
stdout_list.append(returned_instance.stdout)
stderr_list.append(returned_instance.stderr)
returncode_list.append(returned_instance.returncode)

# Check for stdout, stderr and exit status
i = 1
for input_data, output_ref, err_ref in zip(stdin_list, stdout_list, stderr_list):

	# Open, write and close mini_infile
	mini_infile = open(f"mini_infile", "w")
	mini_infile.write(f"{input_data}")
	mini_infile.close()

	# Run the unit
	output = subprocess.run(f"../../minishell < mini_infile", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)

	# Open, write and close outfile, outfile_ref, errfile and erfile_ref
	# Open
	outfile_tmp = open(f"outfile_tmp", "w")
	outfile_ref = open(f"outfile_ref", "w")
	errfile = open(f"errfile", "w")
	errfile_ref = open(f"errfile_ref", "w")
	# Write
	outfile_tmp.write(f"{output.stdout}\n")
	outfile_ref.write(f"{output_ref}\n")
	errfile.write(f"{output.stderr}\n")
	errfile_ref.write(f"{err_ref}\n")
	# Close
	mini_infile.close()
	outfile_tmp.close()
	outfile_ref.close()
	errfile.close()
	errfile_ref.close()

	# Clean outfile  for it to keep only the minishell output
	lines = process_and_modify_file('outfile_tmp')
	outfile = open('outfile', 'w')
	outfile.writelines(lines)
	outfile.close()
	
	print(f"{colours[3]}{i}/{len(stdin_list)}{test_description_list[i-1]}{colours[0]}")

	# Check for stdout
	diff_returned = subprocess.run(f"diff outfile_ref outfile", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
	if diff_returned.returncode != 0:
		print(f"{colours[1]}	KO - stdout{colours[0]}")
		print(f"{colours[4]}stdout diff{colours[0]}")
		print(f"{diff_returned.stdout}")
	else:
		print(f"{colours[2]}	OK - stdout{colours[0]}")

	# Check for stderr
	diff_returned = subprocess.run(f"diff errfile_ref errfile", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
	if diff_returned.returncode != 0:
		print(f"{colours[1]}	KO - stderr{colours[0]}")
		print(f"{colours[4]}stderr diff{colours[0]}")
		print(f"{diff_returned.stdout}")
	else:
		print(f"{colours[2]}	OK - stderr{colours[0]}")

	# # Check for exit status
	# if output.returncode != returncode_list[i-1]:
	# 	print(f"{colours[4]}	KO - exit status{colours[0]}")
	# 	print(f"{colours[4]}exit status diff{colours[0]}")
	# 	print(f"Expected: {returncode_list[i-1]}")
	# 	print(f"Got: {output.returncode}")
	# else:
	# 	print(f"{colours[2]}	OK - exit status{colours[0]}")
	
	# Check for leaks
	subprocess.run(f"{valgrind} ../../minishell < mini_infile", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
	valgrind_status = subprocess.run(f"./valgrind.sh", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
	if (valgrind_status.stdout == '0\n'):
		print(f"{colours[2]}	MOK{colours[0]}")
	else:
		print(f"{colours[1]}	MKO{colours[0]}")

	print("\n------------------------------------\n")
	i = i + 1

# Clean
subprocess.run(f"rm outfile outfile_ref errfile errfile_ref mini_infile outfile_tmp infile", shell=True)
trash = subprocess.run(f"make fclean -C ../../", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)