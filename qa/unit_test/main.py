#!/usr/bin/env python3

status = 0

print("\nUNIT TEST\n")

print("tokenizer")
from tokenizer.unit_tester import unit_tokenizer
_status = unit_tokenizer()
if _status != 0:
	status = 1

print("syntax error")
from syntax_error.unit_tester import unit_syntax_error
_status = unit_syntax_error()
if _status != 0:
	status = 1

print("parser")
from parser.unit_tester import unit_parser
_status = unit_parser()
if _status != 0:
	status = 1

print("expansion")
from expansion.unit_tester import unit_expansion
_status = unit_expansion()
if _status != 0:
	status = 1

print("redirect")
from redirect.unit_tester import unit_redirect
_status = unit_redirect()
if _status != 0:
	status = 1

print("join cmd")
from join_cmd.unit_tester import unit_join_cmd
_status = unit_join_cmd()
if _status != 0:
	status = 1

print("get cmd path")
from get_cmd_path.unit_tester import unit_get_cmd_path
_status = unit_get_cmd_path()
if _status != 0:
	status = 1

print("execute")
from execute.unit_tester import unit_execute
_status = unit_execute()
if _status != 0:
	status = 1

print("exit status")
from exit_status.unit_tester import unit_exit_status
_status = unit_exit_status()
if _status != 0:
	status = 1

from echo.unit_tester import unit_echo
_status = unit_echo()
if _status != 0:
	status = 1

from builtin_cd.unit_tester import unit_cd
_status = unit_cd()
if _status != 0:
	status = 1

from builtin_pwd.unit_tester import unit_pwd
_status = unit_pwd()
if _status != 0:
	status = 1

from builtin_export.unit_tester import unit_export
_status = unit_export()
if _status != 0:
	status = 1

from builtin_unset.unit_tester import unit_unset
_status = unit_unset()
if _status != 0:
	status = 1

from builtin_env.unit_tester import unit_env
_status = unit_env()
if _status != 0:
	status = 1

from builtin_exit.unit_tester import unit_exit
_status = unit_exit()
if _status != 0:
	status = 1

print(f"Status: {status}")