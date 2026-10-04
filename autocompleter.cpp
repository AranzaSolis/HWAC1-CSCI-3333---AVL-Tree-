























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

        //vector that stores all MATCHING entries
        vector<Entry> C;

        //search the part of AVL tree that can contain the matching entries
        completions_recurse(x, root, C);

        //will loop until it finds the 3 most frequent matching words
        //and as long as there are still matching words
        for (int i = 0; i < 3 && !C.empty() > 0; i++)
        {
            //stores first matching word as the one who has the highest frequency
            int highest; 
            //loop thorugh the matching words
            //j=1 because we start at the second element (first element is "highest" at beginning)
            for (int j = 1; j < C.size(); j++)
            {
                //if the current word has higher frequency than current highest
                //make highest the current word
                if(C[j].freq > C[best].fre)
                {
                    highest = j;
                }
            }

            //add most frequent word to T
            T.push_back(C[[highest].s]);
            //remove the added highest word to continue finding next highest
            C.erase(C.begin() + highest);
    }

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
	// Optional helper methods (you'll probably want them)

	// Returns the size of the binary tree rooted at p.
	//
	// Should run in O(n) time.
	int Autocompleter::size_recurse(Node* p)
    {
        //BASE CASE --> no nodes
        if(p==nullptr)
        {
            return 0;
        }

        //store left and right size of subtrees
        int left = size_recurse(p->left);
        int right = size_recurse(p->right);
        //count current node, then all nodes in left and right
        return 1 + left + right;
        
    }

	// Fills C with the completions of x in the BST rooted at p.
	void Autocompleter::completions_recurse(string x, Node* p, vector<Entry> &C)
    {
        //BASE CASE -> no nodes 
        if(p==nullptr)
        {
            return;
        }
        
        //compare beginning of current word with x
        int compare = p->e.s.compare(0, x.size(), x);

        //if current word starts with x, then it is a completion
        if(compare==0)
        {
            //add current word to C
            C.push_back(p->e);

            //search left subtree for more completions (matching words)
            completions_recurse(x, p->left, C);
            //search right subtree for more matching words
            completions_recurse(x, p->right, C);
        }
        //if current word comes before x alphabetically,
        //searach the right subtree
        if(compare < 0)
        {
            completions_recurse(x, p->right, C);
        }
        //if current word comes after x alphabetically,
        //searach the left subtree
        if(compare > 0)
        {
            completions_recurse(x, p->left, C);
        }
    }

	// Inserts an Entry into an AVL tree rooted at p.
	//
	// Should run in O(log(n)) time.
	void Autocompleter::insert_recurse(Entry e, Node* &p)
    {
        //BASE CASE
        if(p==nullptr)
        {
            //create new node with the Entry
            p = new Node(e);
            return; //node was inserted
        }

        //if new word comes before current word alphapbetically
        //insert to left subtree
        if(e.s < p->e.s)
        {
            insert_recurse(e, p->left);
        }
        //if new word comes after current word alphapbetically
        //insert to right subtree
        else if(e.s > p->e.s)
        {
            insert_recurse(e, p->right);
        }
        else //if words are equal (word already in dictionary)
        {
            return; //do nothing
        }

        //rebalance node after insertion
        rebalance(p);
    }

	// Rebalances the AVL tree rooted at p.
	// Helpful for insert().
	// Should be called on every node visited during
	// the search in reverse search order.
	//
	// Should run in O(1) time.
	void Autocompleter::rebalance(Node* &p)
    {
        //update height of current node
        update_height(p);

        //calculate balance
        //negative ->left side is taller
        //positive -> right side is taller
        int balance = height(p->left) - height(p->right);

        //if left subtree is more than 1 level taller
        if(balance > 1)
        {
            //if left subtree's right subtree is taller than left subtree's left subtree
            if(height(p->left->right) > height(p->left->left))
            {
                //Do the left rotation 
                left_rotate(p->left);
            }
            //do right rotation
            right_rotate(p);
        }
        //if right subtree is more than 1 level taller
        else if(balance < -1)
        {
            //if right subtree's left subtree is taller than right subtree's right subtree
            if(height(p->right->left) > height(p->right->right))
            {
                //DO right rotation 
                right_rotate(p->right);
            }
            //then do left rotation
            left_rotate(p);
        }
    }

	// Perform left and right rotations
	// of an AVL tree rooted at p (helpful for implementing rebalance).
	//
	// Should run in O(1) time.
	void Autocompleter::right_rotate(Node* &p)
    {
        node* A = p;
		node* B = p->left;
		node* br = B->right;

		p = B;
		A->left = br;
		B->right = A;

		//update heights
		updateHeight(A);
		updateHeight(B);
    }
	void Autocompleter::left_rotate(Node* &p)
    {
        node* A = p;
		node* B = p->right;
		node* bl = B->left;

		p = B;
		A->right = bl;
		B->left = A;

		//update heights
		updateHeight(A);
		updateHeight(B);
    }
};