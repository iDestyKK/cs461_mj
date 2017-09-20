#!/bin/bash
#
# COSC 461 - Programming Assignment 2: Gradescript (Manual)
#
# Description:
#     Requires "./mj_html2latex", "./html2latex", and all input files that are
#     in "gradescript/input/". The script will loop through all files and pipe
#     them in to both the solution executable and your own executable. Then it
#     will run a diff on both programs' outputs. If the output matches, then
#     it will mark it as "PASSED". Otherwise, it will mark it as "FAILED".
#
#     If you want a version of this gradescript that doesn't rely on the
#     solution executable, then run "gradeall.sh".
#
# Synopsis:
#     ./gradeall2.sh
#
# Author:
#     Clara Van Nguyen
#

# Set up our colours.
red=$(tput setaf 1)
green=$(tput setaf 2)
normal=$(tput sgr 0)

# Check if files exist
if [[ ! -f "html2latex" ]]; then
	printf "[${red}FATAL${normal}] Missing \"html2latex\".\n"
	exit 2
elif [[ ! -f "mj_html2latex" ]]; then
	printf "[${red}FATAL${normal}] Missing \"mj_html2latex\".\n"
	exit 3
fi

# Get number of gradescript cases.
num=0
for i in "gradescript/input/"*".html"; do
	let "num++"
done

# Get number of digits
s=$(echo "$num" | grep -o "[0-9]" | grep -c "")

# Iterate through and compare.
correct=0
c=0
for i in "gradescript/input/"*".html"; do
	fname=$(printf "%03d.tex" $c)
	let "c++"
	str=$(printf "(%*d/%*d) Checking \"%s\"..." $s $c $s $num $fname)
	printf "%-48s" "$str"

	./mj_html2latex < "$i" > "__output1.tex" 2> "err.log"
	if [[ -f "err.log" ]]; then
		printf "[${red}FAILED${normal}]\n"
		printf "[${red}FATAL${normal}] \"mj_html2latex\" failed to execute. Error log below:\n"
		cat "err.log"
		rm -f "err.log" "__output1.tex"
		exit 4
	fi
	./html2latex < "$i" > "__output2.tex"
	diff "__output1.tex" "__output2.tex" 2> /dev/null > /dev/null
	if [[ $? -ne 0 ]]; then
		printf "[${red}FAILED${normal}]\n"
	else
		printf "[${green}PASSED${normal}]\n"
		let "correct++"
	fi
done

rm "__output1.tex" "__output2.tex"
printf "%s out of %s correct.\n" "$correct" "$num"
exit $correct
