#!/usr/bin/env python3

print("\nUNIT TEST\n")

# print("Tokenizer")
# from tokenizer import unit_tester

# print("Syntax Error")
# from syntax_error import unit_tester

# print("Parser")
# from parser import unit_tester

# print("Expansion")
# from expansion import unit_tester

# print("Redirect")
# from redirect import unit_tester

# print("join_cmd")
# from join_cmd import unit_tester

# print("get_cmd_path")
# from get_cmd_path import unit_tester

# print("execute")
# from execute import unit_tester

status = 0

# from builtin_pwd.unit_tester import unit_pwd
# _status = unit_pwd()
# if _status != 0:
# 	status = 1

# from builtin_cd.unit_tester import unit_cd
# _status = unit_cd()
# if _status != 0:
# 	status = 1

# from echo.unit_tester import unit_echo
# _status = unit_echo()
# if _status != 0:
# 	status = 1

# from builtin_env.unit_tester import unit_env
# _status = unit_env()
# if _status != 0:
# 	status = 1

# from builtin_export.unit_tester import unit_export
# _status = unit_export()
# if _status != 0:
# 	status = 1

from builtin_exit.unit_tester import unit_exit
_status = unit_exit()
if _status != 0:
	status = 1

print(f"Status: {status}")