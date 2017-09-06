#include <vector>
#include <map>
#include <string>

using namespace std;

typedef unsigned int uint;

struct NFA_NODE {
	string name;
	vector< vector<string> > states;
	bool final_state;
};

class NFA {
	public:
		//Constructors
		NFA();
		NFA(const string&);
		
		//Process Functions
		void                   read(const string&);

		//Accessor Functions
		vector<NFA_NODE>&      get_nodes();
		map<string, int>&      get_alphabet();
		map<string, NFA_NODE*> get_node_id_map();

		//Get Functions
		NFA_NODE&              get_node(uint);
		int                    get_alphabet_id(const string&);
		NFA_NODE&              get_node_via_id(const string&);
	
	private:
		vector<NFA_NODE> nodes;         //Nodes
		map<string, int> alphabet;      //Pair of Alphabet string and identifier
		map<string, NFA_NODE*> node_id; //Pointer to a node accessable via name
};
