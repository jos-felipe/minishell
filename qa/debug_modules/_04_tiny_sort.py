import subprocess

def	tiny_sort(program, valgrind, valgrind_check, colours):

	# Definig args
	all_tiny_sort_args = [["1", "3", "2"], ["2", "1", "3"], ["2", "3", "1"], ["3", "1", "2"], ["3", "2", "1"]]

	# Defining references
	move_ref_list = ["rra\nsa\n", "sa\n", "rra\n", "ra\n", "ra\nsa\n"]

	# Colecting outputs
	all_outputs = []
	all_outputs_val = []
	for tiny_sort_arg in all_tiny_sort_args:

		cmd = program + tiny_sort_arg
		output = subprocess.run(cmd, stdout=subprocess.PIPE, text=True)
		all_outputs.append(output.stdout)

		cmd_val = valgrind + cmd
		output_val = subprocess.run(cmd_val, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
		all_outputs_val.append(output_val.stderr)
	
	# Checking ref with outputs
	i = 1
	for out, out_val, out_ref in zip(all_outputs, all_outputs_val, move_ref_list):
		print("---------")
		if (out == out_ref):
			print(f"{colours[0]}{i}. OK  {colours[2]}")
		else:
			print(f"{colours[1]}{i}. KO  {colours[2]}")
		if valgrind_check in out_val:
			print(f"{colours[0]}	MOK{colours[2]}")
		else:
			print(f"{colours[1]}   MKO{colours[2]}")
		i = i + 1