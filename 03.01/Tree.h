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
		bool is4er (TreeNode*);
		void printPreorder (TreeNode*);
		void printTableHead ();
		void printTableSep ();
	public:
		Tree ();
		~Tree ();
		void delRescursive (TreeNode*);
		void addNode (string, int, double, int);
		bool searchNode (string);
		void printAll ();
		void printLevelOrder ();
		friend TreeNode * get_anker (Tree & TN);
};
