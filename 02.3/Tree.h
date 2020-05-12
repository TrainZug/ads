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
		void printPreorder (TreeNode*);
	public:
		Tree ();
		~Tree ();
		void delRescursive(TreeNode*);
		void addNode (string, int, double, int);
		void deleteNode (int);
		bool searchNode (string);
		void printAll ();
		friend TreeNode * get_anker (Tree & TN);
};
