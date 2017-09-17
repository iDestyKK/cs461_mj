# PA2 Gradescript

# Set up our colours.
red=$(tput setaf 1)
green=$(tput setaf 2)
normal=$(tput sgr 0)

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
	let "c++"
	str=$(printf "(%*d/%*d) Checking case %03d..." $s $c $s $num $c)
	printf "%-48s" "$str"

	./mj_html2latex < "$i" > "__output1.l"
	./html2latex < "$i" > "__output2.l"
	diff "__output1.l" "__output2.l" 2> /dev/null > /dev/null
	if [[ $? -ne 0 ]]; then
		printf "[${red}FAILED${normal}]\n"
	else
		printf "[${green}PASSED${normal}]\n"
		let "correct++"
	fi
done

rm "__output1.l" "__output2.l"
printf "%s out of %s correct.\n" "$correct" "$num"
exit $correct
