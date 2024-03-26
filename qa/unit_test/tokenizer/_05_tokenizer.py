import subprocess

def tokenizer(command, colours, exit_status):

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
	command_alone_ref = "echo\ncommand:echo|arguments:(null)|input_fd:0|output_fd:1|append:0\nprompt > exit\n"
	command_with_arguments_ref = "echo -n Mephis\ncommand:echo|arguments:-nMephis|input_fd:0|output_fd:1|append:0\nprompt > exit\n"
	redirect_command_output_ref = "echo -n Mephis > outfile\ncommand:echo|arguments:-nMephis|input_fd:0|output_fd:3|append:0\nprompt > exit\n"
	redirect_command_output_append_ref = "echo -n Mephis >> outfile\ncommand:echo|arguments:-nMephis|input_fd:0|output_fd:3|append:1\nprompt > exit\n"
	redirect_command_input_ref = "cat -e < infile\ncommand:cat|arguments:-e|input_fd:3|output_fd:1|append:0\nprompt > exit\n"
	redirect_command_output_and_input_ref = "> outfile cat -e < infile\ncommand:cat|arguments:-e|input_fd:3|output_fd:4|append:0\nprompt > exit\n"
	output_redirect_alone_with_space_ref = "> outfile\ncommand:(null)|arguments:(null)|input_fd:0|output_fd:3|append:0\nprompt > exit\n"
	output_redirect_alone_no_space_ref = ">outfile\ncommand:(null)|arguments:(null)|input_fd:0|output_fd:3|append:0\nprompt > exit\n"
	input_redirect_alone_with_space_ref = "< infile\ncommand:(null)|arguments:(null)|input_fd:3|output_fd:1|append:0\nprompt > exit\n"
	input_redirect_alone_no_space_ref = "<infile\ncommand:(null)|arguments:(null)|input_fd:3|output_fd:1|append:0\nprompt > exit\n"
	output_ref_list = [command_alone_ref, command_with_arguments_ref, redirect_command_output_ref, \
			redirect_command_output_append_ref, redirect_command_input_ref, \
			redirect_command_output_and_input_ref, output_redirect_alone_with_space_ref, \
			output_redirect_alone_no_space_ref, input_redirect_alone_with_space_ref, \
			input_redirect_alone_no_space_ref]
	
	i = 1
	valgrind = "valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=../readline.supp --log-file=valgrind.log"
	for input_data, output_ref in zip(input_data_list, output_ref_list):
		output = subprocess.run(f"{valgrind} ./tokenizer '{input_data}'", stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)

		outfile_content = output.stdout

		if outfile_content == output_ref:
			print(f"{colours[0]}{i}/{len(input_data_list)}.	OK  {colours[2]}")
		else:
			print(f"{colours[1]}{i}/{len(input_data_list)}.	KO  {colours[2]}")
			exit_status = 1
			
		valgrind_status = subprocess.run('./valgrind.sh', stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)

		# Check for leaks
		if (valgrind_status.stdout == '0\n'):
			print(f"{colours[0]}	MOK  {colours[2]}")
		else:
			print(f"{colours[1]}	MKO  {colours[2]}")
			exit_status = 1
		i = i + 1
	

	return (exit_status)
