/*
 * COSC 461 - Programming Assignment 1: NFA2DFA Converter
 *
 * Description:
 *     Converts a (specifically formatted) NFA into a DFA, and exports it to a
 *     humanly readable text file.
 * 
 * Compilation:
 *     This is a C++ program that uses my Handy Library, written in C. As such,
 *     compilation might not be trivial if attempted manually. Please use the
 *     included "makefile".
 *
 * Synopsis:
 *     ./nfa2dfa < nfa_file > dfa_file
 *
 * Author:
 *     Clara Van Nguyen
 */

//C++ Includes
#include <iostream>
#include <string>
#include <vector>
#include <map>

//C Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Library Includes
#include "nfa.hpp"

//Handy (Surprise! It works in C++ too!)
#include "../lib/handy/handy.h"
#include "../lib/handy/types.h"
#include "../lib/handy/file.h"

using namespace std;


uint error_check(int argc, char** argv) {
	//Check Program Parametre
	if (argc != 3) {
		//Clearly you have no idea what you are doing...
		fprintf(stderr, "Usage: %s nfa_file dfa_file\n", argv[0]);
		return 1;
	}

	//Make sure the file exists...
	if (file_exists(argv[1]) == CN_FALSE) {
		fprintf(stderr, "[ERROR] File %s does not exist!\n", argv[1]);
		return 2;
	}

	//Make sure that the output file "doesn't" exist.
	//If it does, offer to overwrite.
	if (file_exists(argv[2]) == CN_TRUE) {
		char buffer[9];
		while (1) {
			printf("File \"%s\" exists. Overwrite? [y/N] ", argv[2]);
			scanf("%s", buffer);
			printf("\n");
			buffer[8] = '\0';
			if (strcmp(buffer, "n") == 0 || strcmp(buffer, "N") == 0) {
				printf("Not overwriting file \"%s\". Exiting...", argv[2]);
				return 3;
			}
			else
			if (strcmp(buffer, "y") == 0 || strcmp(buffer, "Y") == 0) {
				//Well... I guess that old file is history
				break;
			}
		}
	}
	return 0;
}

void print_nfa(NFA& nfa) {
	vector<NFA_NODE>& ref = nfa.get_nodes();
	for (int i = 0; i < ref.size(); i++) {
		printf("%s ", ref[i].name.c_str());
		for (int j = 0; j < ref[i].states.size(); j++) {
			printf("{");
			for (int k = 0; k < ref[i].states[j].size(); k++) {
				printf("%s%s", ref[i].states[j][k].c_str(), (k != ref[i].states[j].size() - 1) ? " " : "");
			}
			printf("} ");
		}
		printf("\n");
	}
	printf("\n\n");
}

int main(int argc, char** argv) {
	//uint error_code = error_check(argc, argv);

	//Assume the user input arguments correctly. Now let us begin.
	//Let's initialise the NFA
	printf("reading NFA... ");
	NFA nfa(argv[1]);
	printf("done.\n");

	
	//Make sure it actually works (Debug)
	//print_nfa(nfa);

	//Do stuff
	nfa.convert_to_dfa();

	//Have a nice day. :)
	return 0;
}
