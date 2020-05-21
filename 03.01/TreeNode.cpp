#include "TreeNode.h"
#include "TreeNode.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

TreeNode::TreeNode (int posId, int nodeId, string name, int alter, double einkommen, int plz) {
	NodePosID = posId;
	NodeID    = nodeId;
	Name      = name;
	Alter     = alter;
	Einkommen = einkommen;
	PLZ       = plz;
	left      = nullptr;
	right     = nullptr;
	red       = true;
}

void TreeNode::print () {
	cout << std::left << setw(3) << setfill(' ') << NodeID << "|";
	cout << std::right << setw(12) << setfill(' ') << Name << "|";
	cout << std::right << setw(7) << setfill(' ') << Alter << "|";
	cout << std::right << setw(11) << setfill(' ') << Einkommen << "|";
	cout << std::right << setw(7) << setfill(' ') << PLZ << "|";
	cout << std::right << setw(7) << setfill(' ') << NodePosID << "| ";
	cout << std::left << setw(7) << setfill(' ') << red << endl;
}
