import subprocess

def user_input(program, valgrind, valgrind_check, colours):

	# Int min and max
	int_max = (2**31) - 1
	int_min = -(2**31)

	# Creating args
	battery = ["ordered_list", "str_on_list", "dup_on_list", "min_on_list", "max_on_list", "nothing_on_list"]
	ordered_list = []
	ordered_range = range(-1, 11, 1)
	for n in ordered_range:
		ordered_list.append(str(n))
	str_on_list = ordered_list[:]
	dup_on_list = ordered_list[:]
	min_on_list = ordered_list[:]
	max_on_list = ordered_list[:]
	nothing_on_list = []
	str_on_list[4] = "abc"
	dup_on_list[9] = "1" 
	min_on_list[4] = str(int_min - 1)
	max_on_list[4] = str(int_max + 1)
	args = [ordered_list, str_on_list, dup_on_list, min_on_list, max_on_list, nothing_on_list]

	# Reference output
	stderr_ref_list = ["", "Error\n", "Error\n", "Error\n", "Error\n", ""]
	stdout_ref_list = ["", "", "", "", "", ""]

	# Runing and colecting output and error
	stdout_list = []
	stderr_list = []
	stderr_val_list = []
	for arg in args:
		cmd = program + arg
		output = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
		cmd_2 = valgrind + cmd
		output_val = subprocess.run(cmd_2, stderr=subprocess.PIPE, text=True)
		stderr_list.append(output.stderr)
		stdout_list.append(output.stdout)
		stderr_val_list.append(output_val.stderr)
		
	# Printing test check
	i = 0
	for out, err, err_val in zip(stdout_list, stderr_list, stderr_val_list):
		print(f"{battery[i].upper()}")
		if ((out == stdout_ref_list[i]) and (err == stderr_ref_list[i])):
			print(f"{colours[0]}{i + 1}. OK{colours[2]}")
		else:
			print(f"{colours[1]}{i + 1}. KO{colours[2]}")
		if valgrind_check in err_val:
			print(f"{colours[0]}	MOK\n{colours[2]}")
		else:
			print(f"{colours[1]}   MKO\n{colours[2]}")
		i = i + 1