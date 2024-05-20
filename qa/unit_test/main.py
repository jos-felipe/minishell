#!/usr/bin/env python3

print("\nUNIT TEST\n")

print("Tokenizer")
from tokenizer import unit_tester

print("Syntax Error")
from syntax_error import unit_tester

print("Parser")
from parser import unit_tester

print("Expansion")
from expansion import unit_tester

print("Redirect")
from redirect import unit_tester

print("join_cmd")
from join_cmd import unit_tester

print("get_cmd_path")
from get_cmd_path import unit_tester

print("execute")
from execute import unit_tester

print("exit status")
from exit_status import unit_tester