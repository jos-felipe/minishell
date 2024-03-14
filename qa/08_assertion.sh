#!/bin/bash

STATUS=0
../minishell < 08_input > outfile
cat outfile | grep 0 > /dev/null
GREP_STATUS=$(echo $?)
if [ "$GREP_STATUS" != "0" ]; then
	STATUS=1
fi
echo $STATUS
