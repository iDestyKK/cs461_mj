#include "nfa.hpp"

#include "lib/handy/file.h"
#include "lib/handy/stream.h"

void explode_bracket(const string& str, vector<string>& vec_ref) {
	//Explodes string separated by "," inside {}'s.
	int i = 1, j, noc = 0;
	vec_ref.clear();

	for (; i < str.size() - 1; i++) {
		if (str[i] != ',') {
			for (j = 0; str[i + j]  != ',' && str[i + j] != '}'; j++);
			if (j == 0)
				continue;
			vec_ref.push_back(str.substr(i, j));
			i += j;
			noc++;
		}
	}
}

void eclosure_calculate(NFA& nfa, NFA_NODE& node) {
	//Computes the Eclosure of a node.
	vector<NFA_NODE*> closure;
	closure.push_back(&node);

	//Go into the node and find out what nodes follow this with "E".
	vector<string>& ref = node.states.back();
	for (int i = 0; i < ref.size(); i++) {
		closure.push_back(nfa.get_node_id_map()[ref[i]]);
		printf("[CHK] %s - 0x%08x vs 0x%08x\n", ref[i].c_str(), &ref[i], nfa.get_node_id_map()[ref[i]]);
	}

	//Make sure we did it right.
	for (int i = 0; i < closure.size(); i++) {
		printf("%s\n", closure[i]->name.c_str());
		//while(1) {};
	}
}

//Constructors
NFA::NFA() {

}

NFA::NFA(const string& fname) {
	read(fname.c_str());
}

NFA::NFA(const char* fname) {
	read(fname);
}

//Process Functions
void NFA::read(const string& fname) {
	read(fname.c_str());	
}

void NFA::read(const char* fname) {
	//This is where the fun begins.
	//First, let's cheat.
	string line;
	vector<string> lines;
	while (getline(cin, line)) {
		lines.push_back(line);
	}
	CN_UINT pos;
	
	//Use CN_SSTREAMs
	CN_SSTREAM ss;
	
	//First line is "Initial State: X".
	for (pos = 1; lines[0][pos - 1] != ':' && lines[0][pos - 1] != '\0'; pos++);
	ss = cn_sstream_init(const_cast<char*>(lines[0].c_str() + pos));
	cn_sstream_next(ss);
	string init_state_str = string(cn_sstream_get(ss));
	cn_sstream_free(ss);

	//Next line is the Final States.
	for (pos = 1; lines[1][pos - 1] != ':' && lines[1][pos - 1] != '\0'; pos++);
	ss = cn_sstream_init(const_cast<char*>(lines[1].c_str() + pos));
	cn_sstream_next(ss);
	explode_bracket(string(cn_sstream_get(ss)), final_state_strs);
	cn_sstream_free(ss);
	
	//Put them in a map as well.
	for (int i = 0; i < final_state_strs.size(); i++)
		final_states[final_state_strs[i]] = true;
	
	//Next line is the total number of states... We can just ignore that since
	//we will be reading from the next line. Moving on... Alphabet

	//Let's use a std::istringstream this time.
	istringstream is(lines[3]);
	string letter;
	is >> letter;
	while (is >> letter) {
		alphabet[letter] = alphabet.size();
	}

	//Finally, let's read the state information.
	for (int cl = 4; cl < lines.size(); cl++) {
		is.clear();
		is.str(lines[cl]);
		CN_UINT id = cl - 4;

		//Let's work magic with this state.
		nodes.push_back(NFA_NODE());
		NFA_NODE& ref = nodes.back();
		
		//Load the Name
		string tmp;
		is >> tmp;
		ref.name = tmp;
		node_id[tmp] = &nodes.back();
		printf("[NOTE] Added %s to map. (0x%08x)\n", ref.name.c_str(), &nodes.back());
		
		//Load the transitions
		vector<string> brackets;
		while (is >> letter) {
			brackets.push_back(letter);
		}

		//Explode the transitions
		for (int i = 0; i < brackets.size(); i++) {
			ref.states.push_back(
				vector<string>()
			);
			vector<string>& vref = ref.states.back();
			explode_bracket(brackets[i], vref);
		}
	}
}

//Accessor Functions
vector<NFA_NODE>& NFA::get_nodes() {
	return nodes;
}

map<string, int>& NFA::get_alphabet() {
	return alphabet;
}

map<string, NFA_NODE*> NFA::get_node_id_map() {
	return node_id;
}

//Get Functions
NFA_NODE& NFA::get_node(uint id) {
	return nodes[id];
}

int NFA::get_alphabet_id(const string& str) {
	return alphabet[str];
}

NFA_NODE& NFA::get_node_via_id(const string& str) {
	return *node_id[str];
}
