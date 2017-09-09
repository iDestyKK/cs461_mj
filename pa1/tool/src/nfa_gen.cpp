/*
 * NFA Input Generator (Extreme Edition)
 * 
 * Description:
 *     Because some people (like me) want to watch the world burn, this program
 *     will generate an input NFA file for the NFA2DFA converter. Feel free to
 *     use it to generate input files and test your program (and the solution
 *     code... which this may or may not break.
 *
 * Synopsis:
 *     ./input_gen alphabet_count state_count absurd_level
 *
 * Author:
 *     Clara Van Nguyen
 */

//C++ Includes
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

//C Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

typedef struct nfa_node {
	string name;
	vector< vector<unsigned int> > states;
	bool final_state;
} NFA_NODE;

typedef struct nfa {
	vector<NFA_NODE> nodes;
} NFA;

string string_to_int(int val) {
	string res;
	ostringstream os;
	os << val;
	res = os.str();
	return res;
}

int main(int argc, char** argv) {
	if (argc != 4) {
		//Clearly you have no idea what you are doing...
		fprintf(stderr, "Usage: %s alphabet_count state_count absurd_level\n", argv[0]);
		return 1;
	}

	srand(time(NULL));

	//Guaranteed to have program arguments at this point. Now let's generate NFA.
	NFA nfa;
	nfa.nodes.resize(atoi(argv[2]));

	string fstate_str = "";
	unsigned int i, j, k,
	             alphabet_size = atoi(argv[1]),
	             absurd_level  = atoi(argv[3]);

	for (i = 0; i < nfa.nodes.size(); i++) {
		NFA_NODE& ref = nfa.nodes[i];
		ref.name = string_to_int(i + 1);
		ref.states.resize(alphabet_size);
		ref.final_state = ((rand() % 100000) < (1000 * absurd_level));
		if (ref.final_state) {
			if (fstate_str != "")
				fstate_str += ",";
			fstate_str += ref.name;
		}
		for (j = 0; j < alphabet_size; j++) {
			if ((rand() % 11) < (5 + (absurd_level * 0.5))) {
				unsigned int num = 1 + (rand() % 4), sentaku;
				set<unsigned int> tally;
				for (k = 0; k < num; k++) {
					while (true) {
						sentaku = rand() % nfa.nodes.size();
						if (sentaku != i && tally.find(sentaku) == tally.end())
							break;
					}
					tally.insert(sentaku);
					ref.states[j].push_back(sentaku);
				}
			}
		}
	}


	//If there still isn't a final state, just pick one
	if (fstate_str == "") {
		fstate_str += nfa.nodes[rand() % nfa.nodes.size()].name;
	}


	//Print out this shit...
	cout << "Initial State:  " << (1 + (rand() % nfa.nodes.size())) << endl;;
	cout << "Final States:   {" << fstate_str << "}" << endl;
	cout << "Total States:   " << nfa.nodes.size() << endl;

	//Print out Alphabet information
	cout << "State   ";
	for (i = 0; i < alphabet_size; i++) {
		char yes = 'a' + i;
		if (i == alphabet_size - 1)
			yes = 'E';

		cout << yes << " ";
	}
	cout << endl;

	//Print out State information
	for (i = 0; i < nfa.nodes.size(); i++) {
		NFA_NODE& ref = nfa.nodes[i];
		cout << ref.name << " ";
		for (j = 0; j < alphabet_size; j++) {
			cout << "{";
			for (k = 0; k < ref.states[j].size(); k++) {
				cout << (ref.states[j][k] + 1);
				if (k != ref.states[j].size() - 1)
					cout << ",";
			}
			cout << "} ";
		}
		cout << endl;
	}
}
