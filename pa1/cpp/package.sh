#!/bin/bash

#
# COSC 461 - Homework Packager
#
# Description:
#     Makes my life easier and packages up the files for me with a single
#     command... also helps prevent fuckups like deleting source code.
#     
#     Will make "pkg/master.tar.gz". And it will remove it first if it
#     already exists.
# 
# Author:
#     Clara Van Nguyen
#

red=$(tput setaf 1)
green=$(tput setaf 2)
normal=$(tput sgr0)

printf "COSC 461 PA1 Packager\n\n"

# Forcibly remove the file (even if it doesn't exist!)
printf "%-48s" "Checking if master.tar.gz already exists... "
rm -f "pkg/master.tar.gz"
printf "[  ${green}OK${normal}  ]\n"

# Copy the PDF documentation over
printf "%-48s" "Copying PDF to working_directory... "
cp "doc/pdf/NFA2DFA.pdf" .
printf "[  ${green}OK${normal}  ]\n"

# Tar that shit up
printf "%-48s" "Creating Master TAR... "
tar -czf "pkg/master.tar.gz" makefile *.cpp *.hpp *.pdf lib obj README.md
printf "[  ${green}OK${normal}  ]\n"

# Delete the PDF Copy
printf "%-48s" "Deleting PDF Copy... "
rm "NFA2DFA.pdf"
printf "[  ${green}OK${normal}  ]\n"

# Have a nice day
printf "\nDone! Please go to \"pkg/\" to see your file! :)\n"
