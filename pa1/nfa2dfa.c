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
	CN_VEC states; //CN_VEC< CN_VEC< CN_STRING > >
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
	int i = 1, j, s, c = 0, noc = 0;
	char* tmp;

	//First run, count the number of entries even in the string
	CN_UINT len = strlen(str);
	for (; i < len - 1; i++) {
		if (str[i] != ',') {
			for (j = 0; str[i + j]  != ',' && str[i + j] != '}'; j++);
			if (j == 0)
				continue;
			i += j;
			noc++;
		}
	}

	//Setup Vector
	cn_vec_clear(vec);
	cn_vec_resize(vec, noc);
	printf("VEC ADDR: 0x%08x\n", vec->data);

	for (i = 1; i < len - 1; i++) {
		if (str[i] != ',') {
			for (j = 0; str[i + j] != ',' && str[i + j] != '}'; j++);
			if (j == 0)
				continue;
			char* t = (char*) malloc(sizeof(char) * (j + 1));
			memcpy(t, &str[i], j);
			t[j] = '\0';

			cn_vec_get(vec, CN_STRING, c) = cn_string_from_cstr(t);
			CN_STRING entry = *(CN_STRING*)cn_vec_at(vec, c); //cn_vec_get(vec, CN_STRING, c);

			printf("%s / %s (0x%08x)\n", cn_string_str(entry), t, cn_string_str(entry));
			i += j;
			c++;
		}
	}
	printf("READ: %d\n", c);
}

main(int argc, char** argv) {
	//Perform Error Checking... These things matter y'know.
	CN_UINT error_code = error_check(argc, argv);
	CN_UINT i;

	if (error_code != 0)
		return;

	//Now let's begin the program for real...
	//To begin, let's cheat.
	char** lines = file_to_array(argv[1]);

	//Initialise the NFA
	NFA nfa;
	nfa.alphabet = cn_map_init(char, int, cn_cmp_char);
	nfa.nodes    = cn_vec_init(NFA_NODE);

	//Now let's get the information about the state machine.
	CN_SSTREAM ss;
	CN_UINT pos, init_state, total_states;
	CN_VEC final_states = cn_vec_init(CN_STRING);
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

	//Print out the Alphabet...
	CN_STRING* str_arr = cn_vec_array(final_states, CN_STRING);
	for (i = 0; i < cn_vec_size(final_states); i++) {
		CN_STRING val = str_arr[i];
		printf("ALPHABET: %s\n", cn_string_str(val));
	}

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
		cn_sstream_next(ss);
	}

	//Print out Available Alphabet
	CNM_ITERATOR* beg = cn_map_begin(nfa.alphabet);
	for (; beg->node != NULL; cn_map_next(nfa.alphabet, beg)) {
		printf("%c - %d\n", *(char*)beg->node->key, *(int*)beg->node->data);
	}

	//Set up node Vector, then load in the states.
	NFA_NODE* node_line;
	CN_VEC    push_vec;

	cn_vec_resize(nfa.nodes, total_states);
	NFA_NODE* node_vec = cn_vec_array(nfa.nodes, NFA_NODE);

	for (i = 0; i < cn_vec_size(nfa.nodes); i++) {
		ss = cn_sstream_init(lines[4 + i]);
		cn_sstream_next(ss);
		node_vec[i].name = strdup(cn_sstream_get(ss));

		//Set up state vector as vector of vectors.
		node_vec[i].states = cn_vec_init(CN_VEC*);

		CN_UINT j = 0;
		for (; j < cn_map_size(nfa.alphabet); j++) {
			push_vec = cn_vec_init(CN_STRING);
			cn_sstream_next(ss);
			if (cn_sstream_get(ss) == NULL)
				break;

			explode_bracket(push_vec, cn_sstream_get(ss));
			
			CN_UINT k = 0;
			CN_STRING* ar = cn_vec_array(push_vec, CN_STRING);
			printf("---\n%d\n---\n", cn_vec_size(push_vec));
			for (; k < cn_vec_size(push_vec); k++) {
				//printf("0x%08x - %s\n", ar + k * 4, (char*)ar + k * 4);
				printf("0x%08x - %s\n", (void*)cn_string_str(ar[k]), cn_string_str(ar[k]));
			}
			cn_vec_push_back(node_vec[i].states, &push_vec);
		}

		cn_sstream_free(ss);
	}

	//Let's make sure we have everything..
	//Final States
	for (i = 0; i < cn_vec_size(final_states); i++) {
		printf("%s\n", (char *) cn_vec_at(final_states, i));
	}

	//The actual states
	NFA_NODE* nfa_array = cn_vec_array(nfa.nodes, NFA_NODE);
	CN_UINT j, k;
	for (i = 0; i < cn_vec_size(nfa.nodes); i++) {
		printf("%s ", nfa_array[i].name);
		
		//Now let's look at the states of them
		CN_VEC* arr = cn_vec_array(nfa_array[i].states, CN_VEC);
		for (j = 0; j < cn_vec_size(nfa_array[i].states); j++) {
			CN_STRING* str_arr = cn_vec_array(arr[j], CN_STRING);
			if (cn_vec_size(arr[j]) == 0)
				printf("(null) ");
			for (k = 0; k < cn_vec_size(arr[j]); k++) {
				printf("%s ", cn_string_str(str_arr[k]));
			}
		}

		printf("\n");
	}


	//Free the file line array from memory.
	free_cstr_array(lines);
}
