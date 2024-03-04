import subprocess

def target_position(program, valgrind, valgrind_check, colours):

	# Creating args
	arg = ["13", "5", "1", "11", "-3", "17", "15", "-5", "0", "2", "19"]
	
	# Reference output
	stdout_ref_moves ="ra\nra\npb\nra\npb\nra\nra\npb\npb\nra\nra\npb\npb\npb\npb\nsa\n"
	stdout_ref = stdout_ref_moves + "2 1 1 1 0 0 0 0 \n"
	
	# Runing and colecting output and error
	cmd = program + arg
	output = subprocess.run(cmd, stdout=subprocess.PIPE, text=True)
	output = output.stdout
	
	cmd_val = valgrind + cmd
	output_val = subprocess.run(cmd_val, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
	err_val = output_val.stderr
	
	#Creating test name
	test_name = "Target position"
	
	# Check Ref with output
	print(test_name)
	if (output == stdout_ref):
		print(colours[0] + "1. OK" + colours[2])
	else:
		print(colours[1] + "1. KO" + colours[2])
	if valgrind_check in err_val:
		print(f"{colours[0]}	MOK{colours[2]}")
	else:
		print(f"{colours[1]}   MKO{colours[2]}")