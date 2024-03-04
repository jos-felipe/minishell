import subprocess

def moves(program, valgrind, valgrind_check, colours):

	# Command
	arg = ["6", "5", "4", "3", "2", "1"]
	cmd = program + arg

	# Output references
	move_1 = "rra\n1 6 5 4 3 2 \n"
	move_2 = "ra\n6 5 4 3 2 1 \n"
	move_3 = "sa\n5 6 4 3 2 1 \n"
	move_4 = "sa\n6 5 4 3 2 1 \n"
	move_5 = "pb\npb\npb\npb\npb\npb\n1 2 3 4 5 6 \n"
	move_6 = "rb\n2 3 4 5 6 1 \n"
	move_7 = "rrb\n1 2 3 4 5 6 \n"
	move_8 = "sb\n2 1 3 4 5 6 \n"
	move_9 = "sb\n1 2 3 4 5 6 \n"
	move_10 = "pa\npa\npa\n3 2 1 \n4 5 6 \n"
	move_11 = "rr\n2 1 3 \n5 6 4 \n"
	move_12 = "rrr\n3 2 1 \n4 5 6 \n"
	move_13 = "ss\n2 3 1 \n5 4 6 \n"
	list_of_moves = [move_1, move_2, move_3, move_4, move_5, move_6, move_7, move_8, move_9, move_10, move_11, move_12, move_13]

	# Exec
	output = subprocess.run(cmd, stdout=subprocess.PIPE, text=True)
	string_output = output.stdout
	cmd_2 = valgrind + cmd
	output_val = subprocess.run(cmd_2, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
	err_val = output_val.stderr

	# Geting output
	string_output = output.stdout

	# Searching for each move in the output big string
	i = 1
	for move in list_of_moves:
		operation = move.split("\n")
		print(operation[0])
		if move in string_output:
			print(f"{colours[0]}{i}. OK{colours[2]}")
		else:
			print(f"{colours[1]}{i}. KO{colours[2]}")
		if valgrind_check in err_val:
			print(f"{colours[0]}	MOK{colours[2]}")
		else:
			print(f"{colours[1]}   MKO{colours[2]}")
		i = i + 1
