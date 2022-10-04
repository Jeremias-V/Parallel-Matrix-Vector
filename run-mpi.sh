#!/bin/bash

if [ "$#" -ne 3 ]; then
	echo -e "Correct usage: \n${0} <program_binary> <n_processes> <test_number>"
	echo -e "The result is located in Tests/output.txt"
	exit 1
fi

mpiexec --oversubscribe -np $2 $1 < Tests/$3.txt > Tests/output.txt

exit 0
