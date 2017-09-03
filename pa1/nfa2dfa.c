/*
 * COSC 461 - Programming Assignment 1: NFA2DFA Converter
 *
 * Description:
 *     Converts a (specifically formatted) NFA into a DFA, and exports it to a
 *     humanly readable text file.
 *
 * Compilation:
 *     This C program uses the Handy Library. As such, compiling might not be
 *     trivial if done manually. Please use the "makefile".
 *
 * Synopsis:
 *     ./nfa2dfa nfa_file dfa_file
 * 
 * Author:
 *     Clara Van Nguyen
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Our Secret Weapon
#include "lib/handy/handy.h"
#include "lib/handy/types.h"
#include "lib/handy/file.h"
#include "lib/handy/stream.h"
#include "lib/handy/memory.h"

//CNDS (Clara Nguyen's Data Structures)
#include "lib/handy/cnds/cn_vec.h"
#include "lib/handy/cnds/cn_map.h"
#include "lib/handy/cnds/cn_comp.h"
#include "lib/handy/cnds/cn_string.h"

typedef struct nfa_node {
	char* name;
	CN_VEC states;
	CN_BOOL final;
} NFA_NODE;

typedef struct nfa {
	CN_VEC nodes;    //CN_VEC<NFA_NODE>
	CN_MAP alphabet; //CN_MAP<char, int>
	NFA_NODE* start;
} NFA;

int error_check(int argc, char** argv) {
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

void explode_bracket(CN_VEC vec, char* str) {
	//Gets values inside of a {} bracket and puts them into a specified CN_VEC
	int i = 1, j, s;
	char* tmp;

	CN_UINT len = strlen(str);
	for (; i < len - 1; i++) {
		if (str[i] != ',') {
			for (j = 0; str[i + j] != ','; j++);
			s = atoi(str + i);
			cn_vec_push_back(vec, &s);
			i += j;
		}
	}
}

main(int argc, char** argv) {
	//Perform Error Checking... These things matter y'know.
	CN_UINT error_code = error_check(argc, argv);
	if (error_code != 0)
		return;

	//Now let's begin the program for real...
	//To begin, let's cheat.
	char** lines = file_to_array(argv[1]);

	//Initialise the NFA
	NFA nfa;
	nfa.alphabet = cn_map_init(char, int, cn_cmp_char);

	//Now let's get the information about the state machine.
	CN_SSTREAM ss;
	CN_UINT pos, init_state, total_states;
	CN_VEC final_states = cn_vec_init(CN_UINT);
	char* final_state_str;
	
	//Basically, we will use CN_SSTREAMS and a cool for loop to "skip" to the
	//number. And then we will read it.

	//Initial State
	for (pos =  1; lines[0][pos - 1] != ':' && lines[0][pos - 1] != '\0'; pos++);
	ss = cn_sstream_init(lines[0] + pos);
	cn_sstream_next(ss);
	init_state = atoi(cn_sstream_get(ss));
	cn_sstream_free(ss);

	//Total States
	for (pos =  1; lines[2][pos - 1] != ':' && lines[2][pos - 1] != '\0'; pos++);
	ss = cn_sstream_init(lines[2] + pos);
	cn_sstream_next(ss);
	total_states = atoi(cn_sstream_get(ss));
	cn_sstream_free(ss);

	//Final States is a bit different...
	//Consider the following:
	//    - It is wrapped in {}
	//    - Numbers are separated by "," with no spaces

	for (pos =  1; lines[1][pos - 1] != ':' && lines[1][pos - 1] != '\0'; pos++);
	ss = cn_sstream_init(lines[1] + pos);
	cn_sstream_next(ss);
	final_state_str = strdup(cn_sstream_get(ss));
	cn_sstream_free(ss);
	
	//Explode the string and put the entries in a CN_VEC
	explode_bracket(final_states, final_state_str);

	//Now for state information
	CN_STRING state = cn_string_init();

	//Line 4 is the line that has the NFA language past "State". So let's cheat
	//and use our CN_SSTREAM to get those and put them in a char map.
	ss = cn_sstream_init(lines[3]);

	//Skip NULL and "State" by running next... twice...
	cn_sstream_next(ss);
	cn_sstream_next(ss);

	//Iterate through the line and just get everything...
	for (pos = 0; cn_sstream_get(ss) != NULL; pos++) {
		char a = cn_sstream_get(ss)[0];

		cn_map_insert(nfa.alphabet, &a, &pos);
		printf("Alphabet %d - %c\n", pos, a);
		cn_sstream_next(ss);
	}

	//Free the file line array from memory.
	free_cstr_array(lines);
}
