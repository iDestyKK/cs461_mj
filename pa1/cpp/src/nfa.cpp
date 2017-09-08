#include "nfa.hpp"

#include "../lib/handy/file.h"
#include "../lib/handy/stream.h"

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

void eclosure_calculate(NFA& nfa, DFA_NODE& node, DFA_NODE& res) {
	//Computes the Eclosure of a node.
	set<string> tally;
	vector<NFA_NODE*> closure;
	DFA_NODE construct;

	//Unleash recursion like hell...
	eclosure_calculate_recursive(nfa, node, construct, closure, tally);

	//Make sure we did it right.
	/*for (int i = 0; i < closure.size(); i++) {
		printf("%s\n", closure[i]->name.c_str());
	}*/

	res = DFA_NODE();
	set<string>::iterator ii = tally.begin();
	for (; ii != tally.end(); ii++) {
		res.nodes.push_back(nfa.get_node_id_map()[*ii]);
	}

	generate_dfa_name(res);
}

void eclosure_calculate_recursive(NFA& nfa, DFA_NODE& node, DFA_NODE& construct, vector<NFA_NODE*>& closure, set<string>& tally) {
	//Recursive Helper Function that helps find all "E" transitions for a node in
	//the "eclosure_calculate()" function.
	for (int i = 0; i < node.nodes.size(); i++) {
		NFA_NODE& n_node = *node.nodes[i];
		if (tally.find(n_node.name) == tally.end()) {
			closure.push_back(&n_node);
			tally.insert(n_node.name);
		}

		//Go into the node and find out what nodes follow this with "E".
		vector<string>& ref = n_node.states.back();
		for (int i = 0; i < ref.size(); i++) {
			//O(N) implementation
			/*int j;
			for (j = 0; j < nfa.get_nodes().size(); j++) {
				string& nn = nfa.get_nodes()[j].name;
				if (nn == ref[i] && tally.find(nn) == tally.end()) {
					eclosure_calculate_recursive(nfa, nfa.get_nodes()[j], closure, tally);
					break;
				}
			}*/

			//O(Nlog(N)) implementation
			if (tally.find(ref[i]) == tally.end()) {
				NFA_NODE* node_ref = nfa.get_node_id_map()[ref[i]];
				DFA_NODE tmp;
				node_nfa_to_dfa(*node_ref, tmp);
				eclosure_calculate_recursive(nfa, tmp, construct, closure, tally);
			}
		}
	}
}

void move_dfa(NFA& nfa, DFA_NODE& node, CN_UINT a_id, DFA_NODE& new_node) {
	new_node = DFA_NODE();
	set<string> tally;

	move_dfa_recursive(nfa, node, new_node, a_id, tally);
	generate_dfa_name(new_node);
}

void move_dfa_recursive(NFA& nfa, DFA_NODE& node, DFA_NODE& new_node, CN_UINT a_id, set<string>& tally) {
	//Generates a DFA Node of nodes that we can go to when given an alphabet char
	for (CN_UINT i = 0; i < node.nodes.size(); i++) {
		if (node.nodes[i] == NULL) {
			continue;
		}
		NFA_NODE& ref_node = *node.nodes[i];
		vector<string>& nodes_tg = ref_node.states[a_id];
		for (CN_UINT j = 0; j < nodes_tg.size(); j++) {
			if (tally.find(nodes_tg[j]) == tally.end()) {
				new_node.nodes.push_back(nfa.get_node_id_map()[nodes_tg[j]]);
				DFA_NODE tmp;
				node_nfa_to_dfa(*new_node.nodes.back(), tmp);
				tally.insert(nodes_tg[j]);

				move_dfa_recursive(nfa, tmp, new_node, nfa.get_alphabet().size() - 1, tally);
			}
		}
	}
}

void node_nfa_to_dfa(NFA_NODE& nfa_node, DFA_NODE& dfa_node) {
	dfa_node.name = nfa_node.name;
	dfa_node.nodes.clear();
	dfa_node.states.clear();

	dfa_node.nodes.push_back(&nfa_node);
}

void generate_dfa_name(DFA_NODE& node) {
	set<CN_UINT> node_names;
	ostringstream os;
	for (int i = 0; i < node.nodes.size(); i++)
		node_names.insert(atoi(node.nodes[i]->name.c_str()));

	//Now that they are guaranteed to be in order, generate the string
	set<CN_UINT>::iterator ii = node_names.begin();
	for (; ii != node_names.end(); ii++) {
		if (ii != node_names.begin())
			os << ",";
		os << *ii;
	}
	node.name = os.str();
}

//Constructors
DFA_NODE::DFA_NODE() {
	name = "";
	nodes.clear();
	states.clear();
}

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
		rev_alphabet.push_back(letter);
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
		//node_id.insert(make_pair(tmp, &nodes.back()));
		
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

	for (int i = 0; i < nodes.size(); i++) {
		//Insert pointers into the map... correctly
		node_id.insert(make_pair(
			nodes[i].name,
			&nodes[i]
		));
	}

	//Set up the init_state pointer.
	init_state = node_id[init_state_str];
}

void NFA::convert_to_dfa() {
	//Here is where the magic happens... I guess.
	DFA_NODE dn, res;
	vector< vector< CN_UINT > > transition_states;
	
	//Initial node
	node_nfa_to_dfa(*init_state, dn);
	eclosure_calculate(*this, dn, res);
	dnodes.push_back(res);
	dnames.insert(make_pair(res.name, 0));
	transition_states.push_back(
		vector<CN_UINT>(alphabet.size() - 1)
	);

	//Account for all possibilities and traverse the "graph"
	for (int i = 0; i < dnodes.size(); i++) {
		for (int j = 0; j < alphabet.size() - 1; j++) {
			move_dfa(*this, dnodes[i], j, res);
			if (res.name != "") {
				map<string, int>::iterator ii = dnames.find(res.name);
				if (ii == dnames.end()) {
					dnames.insert(make_pair(res.name, dnames.size()));
					dnodes.push_back(res);
					transition_states.push_back(
						vector<CN_UINT>(alphabet.size() - 1)
					);
					transition_states[i][j] = dnodes.size();
				}
				else {
					//Already exists in the DFA Node List. So...
					transition_states[i][j] = ii->second + 1;
				}
			}
		}
	}

	//Find all final states.
	ostringstream fstates;
	fstates.clear();
	bool cool = false;

	for (int i = 0; i < dnodes.size(); i++) {
		dnodes[i].final_state = false;
		for (int j = 0; j < final_state_strs.size(); j++) {
			if (!dnodes[i].final_state && dnodes[i].name.find(final_state_strs[j]) != string::npos) {
				dnodes[i].final_state = true;
				fstates << ((cool) ? "," : "") << (i + 1);
				cool = true;
			}
		}
	}

	//Print out information.
	printf("\ncreating corresponding DFA ...\n");
	for (int i = 0; i < dnodes.size(); i++) {
		printf("new DFA state:  %-4d -->  {%s}\n", i + 1, dnodes[i].name.c_str());
	}
	printf("done.\n");

	//Print out the nodes
	printf(
		"\nfinal DFA:\n"
		"Initial State:  1\n" //This is pretty much guaranteed...
		"Final States:   {%s}\n"
		"Total States:   %d\n",
		fstates.str().c_str(),
		dnodes.size()
	);
	

	ostringstream os_line;
	os_line.clear();
	os_line << "State   ";
	for (int i = 0; i < rev_alphabet.size() - 1; i++) {
		os_line << setw(16) << left << rev_alphabet[i] << " ";
	}
	printf("%s\n", os_line.str().c_str());

	//Now let's print out each of the nodes
	for (int i = 0; i < dnodes.size(); i++) {
		os_line.clear();
		os_line.str(string());
		os_line << setw(8) << left << dnames[dnodes[i].name] + 1;
		/*printf("%-7d ", dnames[dnodes[i].name] + 1); //, dnodes[i].name.c_str());
		for (int j = 0; j < transition_states[i].size(); j++) {
			printf("%-16d ", transition_states[i][j]);
		}
		printf("\n");*/

		ostringstream os;
		os.clear();
		for (int j = 0; j < transition_states[i].size(); j++) {
			os.clear();
			os.str(string());
			if (transition_states[i][j] != 0)
				os << "{" << transition_states[i][j] << "}";
			else
				os << "{}";

			os_line << setw(16) << left << os.str() << " ";
		}

		printf("%s\n", os_line.str().c_str());
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
