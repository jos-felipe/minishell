import subprocess

def split(program, valgrind, valgrind_check, colours):

	# Creating args
	arg = ["13", "5", "1", "11", "-3", "19", "17", "15", "-5", "0", "2"]
	arg_shell_true = " '13 5 1 11 -3 19 17 15 -5 0 2'"
	program_shell_true = program[0]
	valgrind_shell_true = valgrind[0] + ' ' + valgrind[1] + ' ' + valgrind[2] + ' ' + valgrind[3] + ' '
	
	# Reference output
	stdout_ref_moves = "ra\nra\npb\nra\npb\nra\nra\nra\npb\npb\nra\npb\npb\npb\npb\nra\nsa\n"
	stdout_ref_sort = "pa\n"
	stdout_ref_push_swap = "ra\nra\npa\npa\nra\nra\npa\nrra\nrra\nrra\npa\npa\nra\npa\nra\nra\npa\n"
	stdout_ref_last_sort = "rra\nrra\nrra\n"
	stdout_ref_stack_a = "1 2 3 4 5 6 7 8 9 10 11 \n"
	stdout_ref_stack_b = "\n"

	stdout_ref = stdout_ref_moves + stdout_ref_sort + stdout_ref_push_swap + stdout_ref_last_sort + stdout_ref_stack_a + stdout_ref_stack_b
	
	# Runing and colecting output and error
	cmd_shell_true = program_shell_true + arg_shell_true
	print(cmd_shell_true)
	output = subprocess.run(cmd_shell_true, stdout=subprocess.PIPE, text=True, shell=True)
	output = output.stdout
	
	cmd_val_shell_true = valgrind_shell_true + cmd_shell_true
	print(cmd_val_shell_true)
	output_val = subprocess.run(cmd_val_shell_true, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
	err_val = output_val.stderr
	
	# Creating test name
	test_name = "Split"
	
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