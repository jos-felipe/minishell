import subprocess

def sintax_analysis(command, colours, exit_status):
	
	# Start the C program as a subprocess.
	# process = subprocess.Popen(command, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)

	# Inputs:
	command_alone = "echo\n"
	command_with_arguments = "echo -n Mephis\n"
	redirect_command_output ="echo -n Mephis > outfile\n"
	redirect_command_output_append ="echo -n Mephis >> outfile\n"
	redirect_command_input = "cat -e < infile\n"
	redirect_command_output_and_input = "> outfile cat -e < infile\n"
	output_redirect_alone_with_space = "> outfile\n"
	output_redirect_alone_no_space = ">outfile\n"
	input_redirect_alone_with_space = "< infile\n"
	input_redirect_alone_no_space = "<infile\n"
	input_data_list = [command_alone, command_with_arguments, redirect_command_output, \
			redirect_command_output_append, redirect_command_input, \
			redirect_command_output_and_input, output_redirect_alone_with_space, \
			output_redirect_alone_no_space, input_redirect_alone_with_space, \
			input_redirect_alone_no_space]

	# Outputs references:
	command_alone_ref = "command:echo|arguments:(null)|input_fd:0|output_fd:1|append:0"
	command_with_arguments_ref = "command:echo|arguments:-nMephis|input_fd:0|output_fd:1|append:0"
	redirect_command_output_ref = "command:echo|arguments:-nMephis|input_fd:0|output_fd:3|append:0"
	redirect_command_output_append_ref = "command:echo|arguments:-nMephis|input_fd:0|output_fd:3|append:1"
	redirect_command_input_ref = "command:cat|arguments:-e|input_fd:3|output_fd:1|append:0"
	redirect_command_output_and_input_ref = "command:cat|arguments:-e|input_fd:3|output_fd:4|append:0"
	output_redirect_alone_with_space_ref = "command:(null)|arguments:(null)|input_fd:0|output_fd:3|append:0"
	output_redirect_alone_no_space_ref = "command:(null)|arguments:(null)|input_fd:0|output_fd:3|append:0"
	input_redirect_alone_with_space_ref = "command:(null)|arguments:(null)|input_fd:3|output_fd:1|append:0"
	input_redirect_alone_no_space_ref = "command:(null)|arguments:(null)|input_fd:3|output_fd:1|append:0"
	output_ref_list = [command_alone_ref, command_with_arguments_ref, redirect_command_output_ref, \
			redirect_command_output_append_ref, redirect_command_input_ref, \
			redirect_command_output_and_input_ref, output_redirect_alone_with_space_ref, \
			output_redirect_alone_no_space_ref, input_redirect_alone_with_space_ref, \
			input_redirect_alone_no_space_ref]
	
	i = 1
	for input_data, output_ref in zip(input_data_list, output_ref_list):
		with open('infile.txt', 'w') as file:
			file.write(input_data)
		subprocess.run(f"{command} < infile.txt > outfile.txt 2>errfile.txt", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
		with open('outfile.txt', 'r') as file:
			outfile_content = file.read()
		with open('errfile.txt', 'r') as file:
			outfile_content_valgrind = file.read()

		if outfile_content == output_ref:
			print(f"{colours[0]}{i}/{len(input_data_list)}.	OK  {colours[2]}")
		else:
			print(f"{colours[1]}{i}/{len(input_data_list)}.	KO  {colours[2]}")
			exit_status = 1
		if outfile_content_valgrind != '':
			print(f"{colours[1]}	MKO{colours[2]}")
		else:
			print(f"{colours[0]}	MOK{colours[2]}")
		i = i + 1
	
	# Remove the created files
	subprocess.run("rm infile.txt outfile.txt errfile.txt", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
			
	return (exit_status)
