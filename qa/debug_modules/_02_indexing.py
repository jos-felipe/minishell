import subprocess

def indexing(program, valgrind, valgrind_check, colours):

	battery = "Indexing"

	# Defining arg and output ref
	unordered_list = ["-1", "1", "0", "10", "-10"]
	ranking_list = "2 4 3 5 1 "
	cmd = program + unordered_list

	# Runing cmd and getting output
	output = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
	cmd_2 = valgrind + cmd
	output_val = subprocess.run(cmd_2, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
	err_val = output_val.stderr

	# Printing test check
	print(f"{battery.upper()}")
	if ((output.stdout == ranking_list)):
		print(f"{colours[0]}1. OK{colours[2]}")
	else:
		print(f"{colours[1]}1. KO{colours[2]}")
	if valgrind_check in err_val:
		print(f"{colours[0]}	MOK\n{colours[2]}")
	else:
		print(f"{colours[1]}   MKO\n{colours[2]}")