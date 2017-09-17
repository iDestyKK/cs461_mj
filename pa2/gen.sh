# PA2 input

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
	fname=$(printf "%03d.l" $c)
	let "c++"
	str=$(printf "(%*d/%*d) Generating Solution %s..." $s $c $s $num "$fname")
	printf "%-48s" "$str"

	./mj_html2latex < "$i" > "gradescript/output/$fname"
	printf "[  ${green}OK${normal}  ]\n"
done
