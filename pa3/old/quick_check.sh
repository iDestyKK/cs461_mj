#!/bin/bash

file=$1
./cexpr < $file > test.txt
./ref_cexpr < $file > test2.txt
diff test.txt test2.txt
if [[ $? -ne 0 ]]; then
	vimdiff test.txt test2.txt
fi

#rm test.txt test2.txt
