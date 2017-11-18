#!/bin/bash
#
# Submission Grader for Lab 11
#
# Yeah... it just works
# ~Clara
#

red=$(tput setaf 1)
green=$(tput setaf 2)
normal=$(tput sgr 0)

if [ ! -e "submissions.zip" ]; then
	printf "[FATAL] No \"submissions.zip\" found!\n"
	exit 1
fi

extract_dir="submissions"

# STEP 1
# ---
# Extract submissions

printf "%-56s" "(1 / 4) Extracting \"submissions.zip\"..."
unzip -qq "submissions.zip" -d "./${extract_dir}"
printf "[  ${green}OK${normal}  ]\n"

# STEP 2
# ---
# Each student has two text files... namely "calc" and "float".
# Abuse "awk" to get thir name, time of submission, and file info.

printf "%-56s" "(2 / 4) Organising files for each user..."
cd "./${extract_dir}"
for D in *.txt; do
	uname=$(echo $D | awk -F '[._]' '{print $1}')
	dir="./${uname}"
	mkdir $dir 2> /dev/null
	for F in "$uname"*.txt; do
		fn=$(echo "$F" | cut -f 1,2,3 -d '_' --complement)
		#mv $F $dir/$fn 2> /dev/null

		# HW11 ONLY: Change extension based on file
		if [[ "$fn" == *"calc"* ]]; then
			mv "$F" $dir/"calc.S" 2> /dev/null
		elif [[ "$fn" == *"float"* ]]; then
			mv "$F" $dir/"float.S" 2> /dev/null
		else
			mv "$F" $dir/"$fn" 2> /dev/null
		fi
	done
done
cd ../
printf "[  ${green}OK${normal}  ]\n"

# STEP 3
# ---
# Attempt to compile them all

printf "\n%-56s\n" "(3 / 4) Compiling all..."
cd "./${extract_dir}"
for D in *; do
	rm -f ../*.S ../*.o

	# Copy student work into current directory
	printf "%-56s" "$D"
	cp $D/* ../
	cd ../

	#if [ -e "calc.S" ]; then
		make calc > out_calc.log 2> err_calc.log
	#fi
	stat_calc=$?

	#if [ -e "float.S" ]; then
		make float > out_float.log 2> err_float.log
	#fi
	stat_float=$?

	# Move executable to student directory
	if [ $stat_calc -eq 0 ]; then
		printf "[  ${green}OK${normal}  ] "
		mv calc "./${extract_dir}/$D"
	else
		printf "[${red}FAILED${normal}] "
	fi

	if [ $stat_float -eq 0 ]; then
		printf "[  ${green}OK${normal}  ]\n"
		mv float "./${extract_dir}/$D"
	else
		printf "[${red}FAILED${normal}]\n"
	fi

	cd "./${extract_dir}"
done
cd ../

# STEP 4
# ---
# Run gradescript

printf "\n%-56s\n" "(4 / 4) Executing and Grading..."
cd "./${extract_dir}"
for D in *; do
	rm -f ../*.S ../*.o ../float ../calc

	# Copy student work into current directory
	printf "%-56s" "$D"
	cp $D/* ../
	cd ../

	if [[ -e "calc" || -e "float" ]]; then
		./gradeall.sh > out_calc.log 2> err_calc.log
	else
		# Force the grade value to be 0
		$(exit 0)
	fi

	printf "[ %3d / %3d ]\n" $? 120

	cd "./${extract_dir}"
done


