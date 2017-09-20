#!/bin/bash
#
# COSC 461 - Programming Assignment 2: Gradescript Answer Generator
#
# Description:
#     Requires "./mj_html2latex" and the "gradescript/input/" directory full of
#     HTML files. The script will loop through all of the HTML files, pipe them
#     in to the solution executable, and then pipe the application's output to
#     a file in "gradescript/output/".
#
# Synopsis:
#     ./gen.sh
#
# Author:
#     Clara Van Nguyen
#

# Set up our colours.
red=$(tput setaf 1)
green=$(tput setaf 2)
normal=$(tput sgr 0)

# Check if "mj_html2latex" exists
if [[ ! -f "mj_html2latex" ]]; then
	printf "[${red}FATAL${normal}] \"mj_html2latex\" doesn't exist in current directoy!\n"
	exit 1
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
	str=$(printf "(%*d/%*d) Generating Solution %s..." $s $c $s $num "$fname")
	printf "%-48s" "$str"

	./mj_html2latex < "$i" > "gradescript/output/$fname" 2> "err.log"
	if [[ ! -s "err.log" ]]; then
		rm "err.log"
		printf "[  ${green}OK${normal}  ]\n"
	else
		printf "[${red}FAILED${normal}]\n"
		cat "err.log"
		rm "err.log"
		
		# Let the user know fatal error
		printf "[${red}FATAL${normal}] Can not generate answers. Exiting...\n"
		exit 2
	fi
done
