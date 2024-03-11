#!/bin/bash

PID=$(pidof minishell)
kill -s SIGINT $PID
kill -s SIGQUIT $PID
