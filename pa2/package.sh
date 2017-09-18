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

printf "COSC 461 PA2 Packager\n\n"

# Forcibly remove the file (even if it doesn't exist!)
printf "%-48s" "(1/4) Checking if master.tar.gz already exists."
rm -f "pkg/master.tar.gz"
printf "[  ${green}OK${normal}  ]\n"

# Copy the PDF documentation over
printf "%-48s" "(2/4) Copying files to working_directory."
cp "doc/pdf/HTML2LaTeX.pdf" .
printf "[  ${green}OK${normal}  ]\n"

# Tar that shit up
printf "%-48s" "(3/4) Creating Master TAR."
tar -czf "pkg/master.tar.gz" "Makefile" "html2latex.l" "mj_html2latex" "test.html" "README.md" "gradescript" "check.sh" "gen.sh" "gradeall.sh" "gradeall2.sh"
printf "[  ${green}OK${normal}  ]\n"

# Clean Up
printf "%-48s" "(4/4) Cleaning up."
rm "HTML2LaTeX.pdf"
printf "[  ${green}OK${normal}  ]\n"

# Have a nice day
printf "\nDone! Please go to \"pkg/\" to see your file! :)\n"
