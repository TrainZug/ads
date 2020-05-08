#pragma once
#include <string>
using namespace std;

class TreeNode {
	private:
		int NodePosID;
		int NodeID;
		string Name;
		int Alter;
		double Einkommen;
		int PLZ;
		TreeNode* left;
		TreeNode* right;
	public:
		TreeNode (int posId, int nodeId, string name, int alter, double einkommen, int plz);

		int getNodePosID () {
			return NodePosID;
		}

		int getNodeID () {
			return NodeID;
		}

		string getName () {
			return Name;
		}

		void setName (string s) {
			Name = s;
		}

		int getAlter () {
			return Alter;
		}

		void setAlter (int i) {
			Alter = i;
		}

		double getEinkommen () {
			return Einkommen;
		}

		void setEinkommen (double d) {
			Einkommen = d;
		}

		int getPLZ () {
			return PLZ;
		}

		void setPLZ (int i) {
			PLZ = i;
		}

		TreeNode * getLeft () {
			return left;
		}

		TreeNode * getRight () {
			return right;
		}

		void setLeft (TreeNode* t) {
			left = t;
		}

		void setRight (TreeNode* t) {
			right = t;
		}

		void print ();
};
