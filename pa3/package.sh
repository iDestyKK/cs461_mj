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

printf "COSC 461 PA3 Packager\n\n"

# Forcibly remove the file (even if it doesn't exist!)
printf "%-48s" "(1/5) Checking if *.tar.gz already exists."
rm -f "pkg/*.tar.gz"
printf "[  ${green}OK${normal}  ]\n"

# Copy the PDF documentation over
printf "%-48s" "(2/5) Copying files to working_directory."
cp "doc/pdf/cexpr.pdf" .
printf "[  ${green}OK${normal}  ]\n"

# Tar that shit up
printf "%-48s" "(3/5) Creating Master TAR."
tar -czf "pkg/master.tar.gz" "Makefile" "check.sh" "check2.sh" "gen.sh" "gradeall.sh" "gradeall2.sh" "package.sh" "ex.l" "ex.y" "global.h" "ref_cexpr" "cexpr.pdf" "test" "sample" "old"
printf "[  ${green}OK${normal}  ]\n"

# Tar gradescripts individually too
printf "%-48s" "(4/5) Creating Gradescript TAR."
tar -czf "pkg/gradescript.tar.gz" "check.sh" "check2.sh" "gen.sh" "gradeall.sh" "gradeall2.sh" "gradescript"
printf "[  ${green}OK${normal}  ]\n"

# Clean Up
printf "%-48s" "(5/5) Cleaning up."
rm "cexpr.pdf"
printf "[  ${green}OK${normal}  ]\n"

# Have a nice day
printf "\nDone! Please go to \"pkg/\" to see your files! :)\n"
