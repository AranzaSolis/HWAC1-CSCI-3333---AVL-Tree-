























#include "autocompleter.h"





#include <algorithm>



// Creates a new Autocompleter with an empty dictionary.
	//
	// Must run in O(1) time.
	Autocompleter()
    {
        root = nullptr; //empty tree
    }

	// Adds a string x to the dictionary.
	// If x is already in the dictionary, does nothing.
	//
	// Must run in O(log(n)) time.
	void Autocompleter::insert(string x, int freq)
    {
        //stores a string and a frequency.
        Entry e;

        //store the word inside the Entry
        e.s = x;
        //store frequency inside the Entry
        e.freq = freq;

        //Insert Entry into the AVL tree
        insert_recurse(e, root);

    }

	// Returns the number of strings in the dictionary
	// of possible completions.
	//
	// Must run in O(n) time.
	int Autocompleter::size()
    {
        //call recursive function that counts all string nodes
        //starting from the root
        return size_recurse(root);
    }

	// Fills the vector T with the three most-frequent completions of x.
	// If x has less than three completions, then
	// T is filled with all completions of x.
	// The completions appear in T from most to least frequent.
	//
	// Must run fast.  In particular, you should not search all nodes in the
	// tree for possible completions.
	// Instead, only search regions of the tree for which a completion could
	// be present, which will yield a run time bound of O(k log n ) time,
	// where k is the number of completions in the tree.
	void Autocompleter::completions(string x, vector<string> &T)
    {
        //clears T from previous stored strings
        T.clear();

        //vector that stores all matching entries
        vector<Entry> match;

        //search the part of AVL tree that can contain the matching entries
        completions_recurse(x, root, match)
    }

	// Optional helper methods (you'll probably want them)

	// Returns the size of the binary tree rooted at p.
	//
	// Should run in O(n) time.
	int Autocompleter::ize_recurse(Node* p);

	// Fills C with the completions of x in the BST rooted at p.
	void Autocompleter::completions_recurse(string x, Node* p, vector<Entry> &C);

	// Inserts an Entry into an AVL tree rooted at p.
	//
	// Should run in O(log(n)) time.
	void Autocompleter::insert_recurse(Entry e, Node* &p);

	// Rebalances the AVL tree rooted at p.
	// Helpful for insert().
	// Should be called on every node visited during
	// the search in reverse search order.
	//
	// Should run in O(1) time.
	void Autocompleter::rebalance(Node* &p);

	// Perform left and right rotations
	// of an AVL tree rooted at p (helpful for implementing rebalance).
	//
	// Should run in O(1) time.
	void Autocompleter::right_rotate(Node* &p);
	void Autocompleter::left_rotate(Node* &p);


	//A useful method to update
	//the height of a node,
	//assuming subtrees already have
	//the correct height.
	void Autocompleter::update_height(Node*& p)
	{
		if (p != nullptr)
			p->height = 1 + max(height(p->left), height(p->right));
	}
};