#!/bin/bash

if [ "$#" -ne 2 ]; then
	echo -e "Correct usage: \n${0} <program_binary> <test_number>"
	echo -e "The result is located in Tests/output.txt"
	exit 1
fi

./$1 < Tests/$2.txt > Tests/output.txt

exit 0
