import os

# define user variable
user = os.environ['USER']

def test_collection():

	# Simple
	input_list = ["echo 42"]
	output_ref_list = ["42\n"]
	output_exit_code = ["0\n"]

	# Expansion
	input_list.append("echo $USER")
	output_ref_list.append(f"{user}\n")
	output_exit_code.append("0\n")

	input_list.append("echo $?USER")
	output_ref_list.append("0USER\n")
	output_exit_code.append("0\n")

	input_list.append("echo $abc^def")
	output_ref_list.append("^def\n")
	output_exit_code.append("0\n")

	input_list.append("echo $^def")
	output_ref_list.append("$^def\n")
	output_exit_code.append("0\n")

	input_list.append("echo $USER^def")
	output_ref_list.append(f"{user}^def\n")
	output_exit_code.append("0\n")

	# Command error
	input_list.append("ERR")
	output_ref_list.append("minishell: ERR: command not found\n")
	output_exit_code.append("127\n")

	input_list.append("echo a | ERR b | echo c")
	output_ref_list.append(f"minishell: ERR: command not found\nc\n")
	output_exit_code.append("0\n")

	input_list.append("echo a | echo b | ERR c")
	output_ref_list.append(f"minishell: ERR: command not found\n")
	output_exit_code.append("127\n")

	# Syntax error
	input_list.append("echo 'a b")
	output_ref_list.append(f"minishell: syntax error: unterminated quoted string\n")
	output_exit_code.append("2\n")

	input_list.append("|")
	output_ref_list.append(f"minishell: syntax error near unexpected token\n")
	output_exit_code.append("2\n")

	return input_list, output_ref_list, output_exit_code