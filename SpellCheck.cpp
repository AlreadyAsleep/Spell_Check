# include <iostream>
# include <vector>
# include <string>
# include <fstream>
# include <algorithm>
using namespace std;
struct Node
{
	bool isWord = false;
	vector<Node*> children;//collection of possible next letters or leaf if empty
	char element;
	Node(char c)
	{
		element = c;
	}
	bool isLeaf() const
	{
		return children.size() == 0;
	}
	void addChild(char s)
	{
		Node* node = new Node(s);
		children.push_back(node);//no need to store in alphabetical order 
	}
	void print() const
	{
		cout << element;
	}
	void printChildren() const
	{
		if(children.size() < 1)
			return;
		cout << "{" << children[0]->element;
		for(int i = 1; i < children.size(); i++)
		{
			cout << ", " << children[i]->element; 
		}
		cout << "}" << endl;
	}
	bool equals(Node *node) const
	{
		return element == node->element;
	}
	bool contains(char s)
	{
		for(int i = 0; i < children.size(); i++)
		{
			if(s == children[i]->element)
				return true;
		}
		return false;
	}
	Node* getChild(char s)
	{
		for(int i = 0; i < children.size(); i++)
		{
			if(s == children[i]->element)
				return children[i];
		}
	}
};

class CharTrie
{
public:
	int getCount() const //returns the word count
	{
		return count;
	}
	int getNodeCount() const // returns the node count
	{
		return nodeCount;
	}
	CharTrie()//initializes trie to english letters a-z
	{
		root = new Node('0');
		for(int i = 'a'; i <= 'z'; i++)
		{
			addToRoot((char)i);
		}
	}
	void addWord(string s)
	{
		addWord(s, root);
	}

	bool contains(string s)
	{
		return contains(s, root);
	}
protected:
	void addToRoot(char c)
	{
		root->addChild(c);
	}

	bool contains(string s, Node* node)
	{
		if(node->isWord && s.empty())//node is flagged as word and the string is complete
			return true;
		else if(s.empty() || node->isLeaf())//string is complete or node has no further path
			return false;
		else
		{
			if(node->contains(s[0]))
				return contains(s.substr(1, string::npos), node->getChild(s[0]));
			else
				return false;
		}
	}

	void addWord(string s, Node* node)
	{	
		if(s.empty())//complete word
		{
			node->isWord = true;
			count++;
			return;
		}
		if(node->contains(s[0]))//node for letter already exists
			addWord(s.substr(1, string::npos), node->getChild(s[0]));
		else//adds a node for the given letter and continues
		{
			node->addChild(s[0]);
			nodeCount++;
			addWord(s.substr(1, string::npos), node->getChild(s[0]));
		}
	}
	

	int count = 0;//how many words in the tree
	int nodeCount = 0;// how many nodes (letters) in the tree
	Node* root;//root is place holder with no data element
};

class SpellCheck
{
public: 
	CharTrie trie;
	void loadFile(string path)
	{
		ifstream file (path);
		string s;
		if(file.is_open())
		{
			int i = 0;
			while(getline(file, s))
			{
				transform(s.begin(), s.end(), s.begin(), ::tolower);
				trie.addWord(s);
				i+=s.size();
			}
			file.close();
			cout << "Loaded " << trie.getCount() << " words with " << trie.getNodeCount() << " nodes."<< endl;
			cout << "Average word length: " << (float) i / (float) trie.getCount() << endl;
		}
		else
			cout << "File Error" << endl;
	}

	void check(string s)
	{
		if(trie.contains(s))
			cout << "\nword found" << endl;
		else
			cout << "\nword not found" << endl;
	}
};

int main(int argc, char* argv[])
{
	SpellCheck chk;
	if(argc > 1)
	{
		chk.loadFile(argv[1]);
	}
	else
	{
		cout << "requires file path" << endl;
		return 1;
	}
	while(true)
	{
		cout << "continue?[Y/N] " ;
		char c;
		cin >> c;
		switch(c)
		{
			case 'Y':  break;
			case 'y': break;
			case 'N': return 0; break;
			case 'n': return 0; break;
			default: cout << "error" << endl; return 1; break;
		}
		cout << "Check a word: ";
		string s;
		cin >> s;
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		chk.check(s);
	}
	return 0;
}