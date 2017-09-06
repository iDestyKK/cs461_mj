#include "nfa.hpp"

//Constructors
NFA::NFA() {

}

NFA::NFA(const string& fname) {
	read(fname);
}

//Process Functions
void NFA::read(const string& fname) {
	
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
