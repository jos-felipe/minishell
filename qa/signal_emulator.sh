#!/bin/bash

cd ..
./minishell > outfile
PID=$(pidof minishell)
kill -s SIGINT $PID
kill -s SIGQUIT $PID
