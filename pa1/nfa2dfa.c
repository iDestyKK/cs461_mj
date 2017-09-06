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

//#include "nfa.h"

//Our Secret Weapon... handy
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
	CN_MAP node_id;  //CN_MAP<char*, NFA_NODE*>
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
			free(t);

			i += j;
			c++;
		}
	}
	//printf("READ: %d\n", c);
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
	nfa.node_id  = cn_map_init(char*, NFA_NODE*, cn_cmp_cstr);

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

	//Now for state information
	//CN_STRING state = cn_string_init();

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
	cn_sstream_free(ss);

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
			cn_vec_push_back(node_vec[i].states, &push_vec);
		}

		//Copy a pointer of the data to the node_id map for later.
		cn_map_insert_blank(nfa.node_id, &node_vec[i].name);
		CNM_NODE* fnd = cn_map_find(nfa.node_id, &node_vec[i].name);
		fnd->data = &node_vec[i];

		cn_sstream_free(ss);
	}

	//Let's make sure we have everything..
	//Final States
	for (i = 0; i < cn_vec_size(final_states); i++) {
		printf("%s\n", cn_string_str(cn_vec_get(final_states, CN_STRING, i)));
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

	printf("\n\nMAP POINTERS:\n");

	//And let's check the map pointers as well...
	CNM_ITERATOR* ii = cn_map_begin(nfa.node_id);
	for (; ii->node != NULL; cn_map_next(nfa.node_id, ii)) {
		NFA_NODE* ptr = ii->node->data;
		printf("%s\n", ptr->name);

		//Now let's look at the states of them
		CN_VEC* arr = cn_vec_array(ptr->states, CN_VEC);
		for (j = 0; j < cn_vec_size(ptr->states); j++) {
			CN_STRING* str_arr = cn_vec_array(arr[j], CN_STRING);
			if (cn_vec_size(arr[j]) == 0)
				printf("(null) ");
			for (k = 0; k < cn_vec_size(arr[j]); k++) {
				printf("%s ", cn_string_str(str_arr[k]));
			}
		}

		printf("\n");
	}

	//Free Memory
	CNM_ITERATOR* it;

	//Final States
	for (i = 0; i < cn_vec_size(final_states); i++) {
		cn_string_free(cn_vec_get(final_states, CN_STRING, i));
	}
	cn_vec_free(final_states);
	free(final_state_str);

	//The actual states

	nfa_array = cn_vec_array(nfa.nodes, NFA_NODE);
	for (i = 0; i < cn_vec_size(nfa.nodes); i++) {
		free(nfa_array[i].name);

		//Now let's look at the states of them
		CN_VEC* arr = cn_vec_array(nfa_array[i].states, CN_VEC);
		for (j = 0; j < cn_vec_size(nfa_array[i].states); j++) {
			CN_STRING* str_arr = cn_vec_array(arr[j], CN_STRING);
			for (k = 0; k < cn_vec_size(arr[j]); k++) {
				cn_string_free(str_arr[k]);
			}
			cn_vec_free(arr[j]);
		}
		//cn_vec_free(arr);
		cn_vec_free(nfa_array[i].states);
	}
	cn_vec_free(nfa.nodes);

	//Alphabet, go through the map and free everything
	it = cn_map_begin(nfa.alphabet);
	for (; it->node != NULL;) {
		CNM_NODE* node_ptr = it->node;
		cn_map_next(nfa.alphabet, it);
		__cn_map_free_node(node_ptr);
	}
	cn_map_free(nfa.alphabet);

	it = cn_map_begin(nfa.node_id);
	for (; it->node != NULL;) {
		CNM_NODE* node_ptr = it->node;
		node_ptr->data = NULL;
		cn_map_next(nfa.node_id, it);
		__cn_map_free_node(node_ptr);
	}
	cn_map_free(nfa.node_id);

	free(it);


	//Free the file line array from memory.
	free_cstr_array(lines);
}
