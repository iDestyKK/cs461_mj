#!/bin/bash

#
# COSC 461 - Programming Assignment 2: Checker Script
#
# Description:
#     Checks if ./html2latex matches with ./mj_html2latex. In order to do the
#     comparison, both the ./html2latex and ./mj_html2latex executables must be
#     in the same directory as this shell script. Then run "./check.sh" while
#     it has the "x" permission (chmod +x check.sh). It'll tell you if it does
#     not match the solution code.
#
# Synopsis:
#     ./check.sh html_file
#
# Author:
#     Clara Van Nguyen
#

if [[ $# -ne 1 ]]; then
	printf "Usage: %s html_file\n" "$0"
	exit -1
fi

./mj_html2latex < "$1" > "__output1.l"
./html2latex < "$1" > "__output2.l"

diff "__output1.l" "__output2.l" 2> /dev/null > /dev/null
if [[ $? -ne 0 ]]; then
	x='';
	while [[ "$x" -ne 'y' && "$x" -ne 'N' ]]; do
		printf "Does not match! Would you like to see a diff -y? [y/N]"
		read -n x
	done;

	if [[ "$x" -eq 'y' ]]; then
		#diff -y "__output1.l" "__output2.l" | less
		vimdiff "__output1.l" "__output2.l"
	fi
	

else
	printf "Matches!\n"
fi

rm -rf "__output1.l" "__output2.l"
