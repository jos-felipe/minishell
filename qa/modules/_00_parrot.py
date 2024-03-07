import subprocess

def parrot(colours, exit_status):
	# Start the C program as a subprocess.
	process = subprocess.Popen(["../minishell"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

	# Inputs.
	input_data = ["1\n", "2\n", "3\n"]
	output_ref = ["1\n", "2\n", "3\n"]

	# lists for colection of outputs.
	output_list = []

	# Send inputs to minishel prompt and collecting outputs.
	for data in input_data:
		# Send input to the C program
		process.stdin.write(data)
		process.stdin.flush()  # Make sure to flush the input buffer

		# Read output from the C program
		process.stdout.readline()
		output = process.stdout.readline()
		output_list.append(output)

	# Print the output
	i = 1
	for output, ref in zip(output_list, output_ref):
		if (output == ref):
			print(f"{colours[0]}{i}/{len(input_data)}.	OK  {colours[2]}")
		else:
			print(f"{colours[1]}{i}/{len(input_data)}.	KO  {colours[2]}")
			exit_status = 1
		i = i + 1

	# Kill minishel process.
	unused_trash = subprocess.run('pkill minishell', stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)

	return (exit_status)