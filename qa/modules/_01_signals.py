# Checks keybord interrupt signals in minishell prompt.: 
# ^C = gives user a new prompt
# ^D = exits prompt
# ^\ = does nothing

# How to send keyboard signals to a subprocess in Python?
# proc.send_signal(signal.SIGINT)
# proc.send_signal(signal.SIGQUIT)
# proc.stdin.close()

import subprocess
import signal

def signals(colours, exit_status):
	# Start the C program as a subprocess.
	process = subprocess.Popen(["../minishell"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

	# Inputs.
	input_data = ["1\n", "2\n", "3\n"]
	output_ref = ["1\n", "2\n", "3\n"]

	# lists for colection of outputs.
	output_list = []

	# Sigint_out
	sigint_out = []
	sigint_out_ref = ["prompt >^C", "prompt >"]

	process.stdin.write("melvin\n")
	process.stdin.flush()
	sigint_out.append(process.stdout.readline())
	process.send_signal(signal.SIGINT)
	sigint_out.append(process.stdout.readline())
	process.stdin.write("melvin\n")
	process.stdin.flush()
	sigint_out.append(process.stdout.readline())
	sigint_out.append(process.stdout.readline())
	sigint_out.append(process.stdout.readline())
	print(sigint_out)

	# Sigquit_out
	# sigquit_out = []
	# sigquit_out_ref = ["prompt > "]

	# process.send_signal(signal.SIGQUIT)
	# sigint_out.append(process.stdout.readline())
	# print(sigquit_out)

	# CTRL+D exit_out
	# exit_out = ""
	# exit_out_ref = "prompt > exit"

	# process.stdin.close()
	# exit_out = process.stdout.readline()
	# print(exit_out)

	# # Print the output
	# i = 1
	# for output, ref in zip(output_list, output_ref):
	# 	if (output == ref):
	# 		print(f"{colours[0]}{i}/{len(input_data)}.	OK  {colours[2]}")
	# 	else:
	# 		print(f"{colours[1]}{i}/{len(input_data)}.	KO  {colours[2]}")
	# 		exit_status = 1
	# 	i = i + 1

	# Kill minishel process.
	unused_trash = subprocess.run('pkill minishell', stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)

	return (exit_status)