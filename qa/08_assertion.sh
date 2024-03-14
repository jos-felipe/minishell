#!/bin/bash

STATUS=0
../minishell < 08_command_list > outfile
cat outfile | grep 0 > /dev/null
GREP_STATUS=$(echo $?)
if [ "$GREP_STATUS" != "0" ]; then
	STATUS=1
fi
echo $STATUS
