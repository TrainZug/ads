#include "Tree.h"
#include "TreeNode.h"
#include <iostream>
#include <iomanip>

using namespace std;

Tree::Tree () {
	anker         = nullptr;
	NodeIDCounter = 0;
}

Tree::~Tree () {
	delRescursive(anker);
}

void Tree::delRescursive (TreeNode* tmp) {
	if (tmp != nullptr)
	{
		delRescursive(tmp->getLeft());
		delRescursive(tmp->getRight());
		delete tmp;
	}
}



void Tree::addNode (string name, int alter, double einkommen, int plz) {
	TreeNode* neu = new TreeNode(alter + einkommen + plz, NodeIDCounter++, name, alter, einkommen, plz);
	if (anker == nullptr) {
		// leerer baum
		anker = neu;
	} else {
		TreeNode* tmp    = anker;
		TreeNode* parent = nullptr;
		while (tmp != nullptr) {
			parent = tmp;
			if (neu->getNodePosID() > tmp->getNodePosID()) {
				// neu > alt dann rechts sonst links
				tmp = tmp->getRight();
			} else {
				tmp = tmp->getLeft();
			}
		}
		if (parent != nullptr) {
			if (neu->getNodePosID() > parent->getNodePosID()) {
				// gucken ob links oder rechts im parent
				parent->setRight(neu);
			} else {
				parent->setLeft(neu);
			}
		}
	}
}

void Tree::deleteNode (int posId) {

	// leerer Baum
	if (anker == nullptr)
		return;

	TreeNode* gefundener_knoten = anker;
	TreeNode* parent            = nullptr;
	TreeNode * tmp1, * tmp2;

	// Knoten suchen und parent davon speichern
	while (gefundener_knoten != nullptr && posId != gefundener_knoten->getNodePosID()) {
		parent = gefundener_knoten;
		if (posId > gefundener_knoten->getNodePosID())
			gefundener_knoten = gefundener_knoten->getRight();
		else
			gefundener_knoten = gefundener_knoten->getLeft();
	}
	if (gefundener_knoten == nullptr) {
		return;
	}

	// Blatt: keine Nachfolger
	if (gefundener_knoten->getLeft() == nullptr && gefundener_knoten->getRight() == nullptr) {
		tmp2 = nullptr;

		// nur linken Nachfolger
	} else if (gefundener_knoten->getLeft() == nullptr && gefundener_knoten->getRight() != nullptr) {
		tmp2 = gefundener_knoten->getRight();

	} else if (gefundener_knoten->getLeft() != nullptr && gefundener_knoten->getRight() == nullptr) {
		tmp2 = gefundener_knoten->getLeft();

		// linken und rechten Nachfolger
	} else {
		tmp1 = gefundener_knoten;             // parent vom min
		tmp2 = gefundener_knoten->getRight(); // min im rechten teilbaum suchen

		// min und parent von min suchen
		while (tmp2->getLeft() != nullptr) {
			tmp1 = tmp2;
			tmp2 = tmp2->getLeft();
		}
		tmp2->setLeft(gefundener_knoten->getLeft()); // Minimum links übernimmt linken Teilbaum von gefundenem
		if (tmp1 != gefundener_knoten) {
			tmp1->setLeft(tmp2->getRight());               // neues Minimum übernimmt rechten Teilbaum von alten Minimum
			tmp2->setRight(gefundener_knoten->getRight()); // Minimum rechts übernimmt rechten Teilbaum von gefundenem
		}
	}

	// Knoten löschen und Elternknoten aktualisieren
	if (parent == nullptr) // erster knoten
		anker = tmp2;
	else if (parent->getLeft() == gefundener_knoten) // in parent left oder right neu machen
		parent->setLeft(tmp2);                       // 
	else
		parent->setRight(tmp2);

	delete gefundener_knoten;
}

bool Tree::searchNode (string name) {
	bool gefunden = false;
	cout << "+ Fundstellen:" << endl;
	searchNodes(anker, name, gefunden);
	return gefunden;
}

void Tree::searchNodes (TreeNode* tmp, string name, bool & gefunden) {
	if (tmp != nullptr) {
		searchNodes(tmp->getLeft(), name, gefunden);
		if (tmp->getName() == name) {
			gefunden = true;
			tmp->print();
		}
		searchNodes(tmp->getRight(), name, gefunden);
	}
}

void Tree::printPreorder (TreeNode* tmp) {
	if (anker == tmp) {
		if (tmp == nullptr) {
			cout << "Keine Einträge vorhanden" << endl;
			return;
		}
		cout << "ID | Name\t| Alter\t| Einkommen | PLZ   | Pos\t" << endl;
		cout << "---+------------+-------+-----------+-------+-------" << endl;
	} else if (tmp == nullptr) {
		return;
	}

	tmp->print();

	printPreorder(tmp->getLeft());
	printPreorder(tmp->getRight());
}

void Tree::printAll () {
	printPreorder(anker);
}
