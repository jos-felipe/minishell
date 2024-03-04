import subprocess

def sort(program, valgrind, valgrind_check, colours):

	# Creating args
	arg = ["13", "5", "1", "11", "-3", "19", "17", "15", "-5", "0", "2"]
	
	# Reference output
	stdout_ref_moves = "ra\nra\npb\nra\npb\nra\nra\nra\npb\npb\nra\npb\npb\npb\npb\nra\nsa\n"
	stdout_ref_sort = "pa\n"
	stdout_ref_stack_a = "11 5 9 10 \n"
	stdout_ref_stack_b = "7 6 8 3 1 2 4 \n"

	stdout_ref = stdout_ref_moves + stdout_ref_sort + stdout_ref_stack_a + stdout_ref_stack_b
	
	# Runing and colecting output and error
	cmd = program + arg
	output = subprocess.run(cmd, stdout=subprocess.PIPE, text=True)
	output = output.stdout
	
	cmd_val = valgrind + cmd
	output_val = subprocess.run(cmd_val, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
	err_val = output_val.stderr
	
	#Creating test name
	test_name = "First move"
	
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