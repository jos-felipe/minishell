import subprocess

def pre_sort(program, valgrind, valgrind_check, colours):

	# Creating args
	sorted_list = []
	sorted_range = range(0, 10, 1)
	for n in sorted_range:
		sorted_list.append(str(n))
	unsorted_list = ["13", "5", "1", "11", "-3", "17", "15", "-5", "0", "2", "19"]

	# Reference output
	stdout_ref_sorted = ""
	stdout_ref_moves ="ra\nra\npb\nra\npb\nra\nra\npb\npb\nra\nra\npb\npb\npb\npb\nsa\n"
	stdout_ref_sorted_3 = "2 15 19 \n17 11 5 13 0 -5 -3 1 \n"
	stdout_ref_unsorted = stdout_ref_moves + stdout_ref_sorted_3

	# Runing and colecting output and error
	cmd1 = program + sorted_list
	output_sorted = subprocess.run(cmd1, stdout=subprocess.PIPE, text=True)
	output1 = output_sorted.stdout
	cmd1 = valgrind + cmd1
	output_sorted_val = subprocess.run(cmd1, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
	err_val_1 = output_sorted_val.stderr
	
	cmd2 = program + unsorted_list
	output_unsorted = subprocess.run(cmd2, stdout=subprocess.PIPE, text=True)
	output2 = output_unsorted.stdout
	cmd2 = valgrind + cmd2
	output_unsorted_val = subprocess.run(cmd2, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
	err_val_2 = output_unsorted_val.stderr

	#Creating test names
	test_names = ["Sorted list", "Unsorted list"]
	outputs = [output1, output2]
	err_vals = [err_val_1, err_val_2]
	stdout_refs = [stdout_ref_sorted, stdout_ref_unsorted]

	# Check Ref with output
	for test_name, output, err_val, stdout_ref in zip(test_names, outputs, err_vals, stdout_refs):
		print(test_name)
		if (output == stdout_ref):
			print(colours[0] + "1. OK" + colours[2])
		else:
			print(colours[1] + "1. KO" + colours[2])
		if valgrind_check in err_val:
			print(f"{colours[0]}	MOK{colours[2]}")
		else:
			print(f"{colours[1]}   MKO{colours[2]}")
