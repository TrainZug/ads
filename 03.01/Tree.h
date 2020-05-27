#pragma once
#include "TreeNode.h"
#include <string>
#include "catch.h"
using namespace std;

class Tree {
	private:
		TreeNode* anker;
		int NodeIDCounter;
		void searchNodes (TreeNode*, string, bool &);
		TreeNode * deleteNode (TreeNode*, int);
		TreeNode * minNode (TreeNode*);
		TreeNode * maxNode (TreeNode*);
		bool split4Node (TreeNode*);
		bool rotateTreeRight (TreeNode*, TreeNode*);
		bool rotateTreeLeft (TreeNode*, TreeNode*);
		bool is4er (TreeNode*);         // ueberpruefen ob 4er knoten
		void printPreorder (TreeNode*); // recursive preorder
		void printTableHead ();         // ausgabe von tabellenkopf
		void printTableSep ();          // ausgabe von ---------------
		void delRescursive (TreeNode*); // dekonstruktor recursive loeschen
	public:
		Tree ();
		~Tree ();
		bool addNode (string, int, double, int);
		bool searchNode (string);
		void printAll ();
		void printLevelOrder ();
		friend TreeNode * get_anker (Tree & TN);
};