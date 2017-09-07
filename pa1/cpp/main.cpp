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
#include "lib/handy/handy.h"
#include "lib/handy/types.h"
#include "lib/handy/file.h"

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

int main(int argc, char** argv) {
	//uint error_code = error_check(argc, argv);

	//Assume the user input arguments correctly. Now let us begin.
	//Let's initialise the NFA
	NFA nfa(argv[1]);

	//Now let's make sure everything works.
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
	eclosure_calculate(nfa, nfa.get_nodes()[6]);
}
