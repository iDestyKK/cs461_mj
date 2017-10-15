#!/bin/bash

# Set up our colours
red=$(tput setaf 1)
green=$(tput setaf 2)
normal=$(tput sgr 0)

# Make our directories
mkdir "../gradescript" 2> /dev/null > /dev/null
mkdir "../gradescript/input" 2> /dev/null > /dev/null
mkdir "../gradescript/output" 2> /dev/null > /dev/null

c=0

# First 10 cases are simple.
for i in {0..9}; do
	name=$(printf "%03d" $i);
	let "c++"
	str=$(printf "(%*d/%*d) Generating Input %s..." 3 $c 3 125 "$name")	
	printf "%-48s" "$str"
	node gen.js 10 1 > "../gradescript/input/${name}.txt"
	printf "[  ${green}OK${normal}  ]\n"
done

# Next 20 are a bit more brutal
for i in {10..29}; do
	name=$(printf "%03d" $i);
	let "c++"
	str=$(printf "(%*d/%*d) Generating Input %s..." 3 $c 3 125 "$name")	
	printf "%-48s" "$str"
	node gen.js 30 10 > "../gradescript/input/${name}.txt"
	printf "[  ${green}OK${normal}  ]\n"
done

# 30-49 too.
for i in {30..49}; do
	name=$(printf "%03d" $i);
	let "c++"
	str=$(printf "(%*d/%*d) Generating Input %s..." 3 $c 3 125 "$name")	
	printf "%-48s" "$str"
	node gen.js 50 50 > "../gradescript/input/${name}.txt"
	printf "[  ${green}OK${normal}  ]\n"
done

# 50-69 too... :>.>:
for i in {50..69}; do
	name=$(printf "%03d" $i);
	let "c++"
	str=$(printf "(%*d/%*d) Generating Input %s..." 3 $c 3 125 "$name")	
	printf "%-48s" "$str"
	node gen_a.js 75 75 > "../gradescript/input/${name}.txt"
	printf "[  ${green}OK${normal}  ]\n"
done

# 70-89 are getting way more serious
for i in {70..89}; do
	name=$(printf "%03d" $i);
	let "c++"
	str=$(printf "(%*d/%*d) Generating Input %s..." 3 $c 3 125 "$name")	
	printf "%-48s" "$str"
	node gen_a.js 100 100 > "../gradescript/input/${name}.txt"
	printf "[  ${green}OK${normal}  ]\n"
done

# 90-99 are the most difficult
for i in {90..99}; do
	name=$(printf "%03d" $i);
	let "c++"
	str=$(printf "(%*d/%*d) Generating Input %s..." 3 $c 3 125 "$name")	
	printf "%-48s" "$str"
	node gen_a.js 500 125 > "../gradescript/input/${name}.txt"
	printf "[  ${green}OK${normal}  ]\n"
done

# 100-122 are extra stuff to make sure yours matches his
for i in {100..122}; do
	name=$(printf "%03d" $i);
	let "c++"
	str=$(printf "(%*d/%*d) Generating Input %s..." 3 $c 3 125 "$name")	
	printf "%-48s" "$str"
	node gen_a.js 1000 100 > "../gradescript/input/${name}.txt"
	printf "[  ${green}OK${normal}  ]\n"
done

# 123 is brutal test #1.
name=$(printf "%03d" 123);
let "c++"
str=$(printf "(%*d/%*d) Generating Input %s..." 3 $c 3 125 "$name")	
printf "%-48s" "$str"
node gen_a.js 5000 2 > "../gradescript/input/${name}.txt"
printf "[  ${green}OK${normal}  ]\n"

# 124 is the final brutal test. Good Luck.
name=$(printf "%03d" 124);
let "c++"
str=$(printf "(%*d/%*d) Generating Input %s..." 3 $c 3 125 "$name")	
printf "%-48s" "$str"
node gen_a.js 10000 10 > "../gradescript/input/${name}.txt"
printf "[  ${green}OK${normal}  ]\n"
