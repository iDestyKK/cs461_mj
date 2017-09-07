#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <queue>

#include "lib/handy/types.h"

using namespace std;

typedef unsigned int uint;

struct NFA_NODE {
	string name;
	vector< vector<string> > states;
	bool final_state;
};

struct DFA_NODE {
	DFA_NODE();
	string name;
	vector<NFA_NODE*> nodes;  //Collection of nodes.
	vector<DFA_NODE*> states; //Guaranteed to only have one entry
};

class NFA {
	public:
		//Constructors
		NFA();
		NFA(const string&);
		NFA(const char*);
		
		//Process Functions
		void                   read(const string&);
		void                   read(const char*);
		void                   convert_to_dfa();

		//Accessor Functions
		vector<NFA_NODE>&      get_nodes();
		map<string, int>&      get_alphabet();
		map<string, NFA_NODE*> get_node_id_map();

		//Get Functions
		NFA_NODE&              get_node(uint);
		int                    get_alphabet_id(const string&);
		NFA_NODE&              get_node_via_id(const string&);
	
	private:
		vector<NFA_NODE>       nodes;        //Nodes
		map<string, int>       alphabet;     //Pair of Alphabet string and identifier
		vector<string>         rev_alphabet; //Reverse lookup for Alphabet.
		map<string, NFA_NODE*> node_id;      //Pointer to a node accessable via name
		map<string, bool>      final_states; //IDs of all final states
		vector<string>         final_state_strs;
		NFA_NODE*              init_state;   //Pointer to initial state

		vector<DFA_NODE>       dnodes;       //Nodes when converting to DFA
		map<string, int>       dnames;       //Names to make sure no duplicates exist
};

void explode_bracket(const string&, vector<string>&);
void eclosure_calculate(NFA&, DFA_NODE&, DFA_NODE&);
void eclosure_calculate_recursive(NFA&, DFA_NODE&, DFA_NODE&, vector<NFA_NODE*>&, set<string>&);
void node_nfa_to_dfa(NFA_NODE&, DFA_NODE&);
void move_dfa(NFA&, DFA_NODE&, CN_UINT, DFA_NODE&);
void move_dfa_recursive(NFA&, DFA_NODE&, DFA_NODE&, CN_UINT, set<string>&);
void generate_dfa_name(DFA_NODE&);
