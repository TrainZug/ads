#include "Tree.h"
#include "TreeNode.h"
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>

using namespace std;

Tree::Tree () {
	anker         = nullptr;
	NodeIDCounter = 1; // weil der test es so viel 
}

Tree::~Tree () {
	delRescursive(anker);
}

void Tree::delRescursive (TreeNode* tmp) {
	if (tmp != nullptr) {
		delRescursive(tmp->getLeft());
		delRescursive(tmp->getRight());
		delete tmp;
	}
}

void Tree::addNode (string name, int alter, double einkommen, int plz) {
	TreeNode* neu = new TreeNode(alter + einkommen + plz, NodeIDCounter++, name, alter, einkommen, plz);
	if (anker == nullptr) {
		anker = neu;
		neu->setRed(false); // wurzel ist schwarz
	} else {
		vector<TreeNode*> visited;
		TreeNode* tmp    = anker;
		TreeNode* parent = nullptr;
		while (tmp != nullptr) {

			parent = tmp;

			if (neu->getNodePosID() < tmp->getNodePosID()) {
				tmp = tmp->getLeft();
			} else {
				tmp = tmp->getRight();
			}

			if (is4er(parent)) {
				split4Node(parent);
			}

			visited.push_back(parent);

		}

		// einfügen
		neu->setParent(parent);
		if (neu->getNodePosID() > parent->getNodePosID()) {
			parent->setRight(neu);
		} else {
			parent->setLeft(neu);
		}
		visited.push_back(neu);

		// von neu eingefügten bis wurzel gucken ob zwei rote aufeinander folgen
		for (int i = visited.size() - 1; i >= 0; i--) {
			TreeNode* node = visited[i];
			// beim anker stoppen
			if (node == anker) {
				break;
			}
			TreeNode* parent      = node->getParent();
			TreeNode* grandparent = parent->getParent();
			// aktueller und parent knoten sind rot
			if (node->getRed() && parent->getRed()) {
				// parent ist rechts vom grandparent
				if (grandparent->getRight() == parent) {
					// Knoten sind rechst rechts angeordnet => links-rotation
					if (parent->getRight() == node) {
						rotateTreeLeft(parent, node);
						parent->setRed(false);
						grandparent->setRed(true);
					} else {
						// Knoten sind rechts links angeordnet => rechts-links rotation
						rotateTreeRight(node, node->getLeft());
						rotateTreeLeft(node, parent);
						node->setRed(false);
						grandparent->setRed(true);
					}
				} else { // parent ist links vom grandparent
					// Knoten sind links links angeordnet => rechts-rotation
					if (parent->getLeft() == node) {
						rotateTreeRight(parent, node);
						parent->setRed(false);
						grandparent->setRed(true);
					} else {
						// Knoten sind links rechts angeordnet => links-rechts-rotation
						rotateTreeLeft(node, node->getRight());
						rotateTreeRight(node, parent);
						node->setRed(false);
						grandparent->setRed(true);
					}
				}
			}
		}

	}
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

bool Tree::split4Node (TreeNode* tmp) {

	if (is4er(tmp)) {

		if (tmp != anker) {
			tmp->setRed(true);
		}

		tmp->getLeft()->setRed(false);
		tmp->getRight()->setRed(false);

		return true;
	}

	return false;
}

void Tree::printPreorder (TreeNode* tmp) {

	if (tmp == nullptr) {
		return;
	}

	tmp->print();

	printPreorder(tmp->getLeft());
	printPreorder(tmp->getRight());
}

void Tree::printAll () {
	if (anker == nullptr) {
		cout << "Keine Einträge vorhanden" << endl;
		return;
	}

	printTableHead();
	printTableSep();
	printPreorder(anker);
	printTableSep();
}

void Tree::printLevelOrder () {
	if (anker == nullptr) {
		cout << "Keine Einträge vorhanden" << endl;
		return;
	}

	printTableHead();
	printTableSep();

	// Levelorder als Binärbaum
	queue<TreeNode*> q;
	q.push(anker); // anker reintun
	while (!q.empty()) {
		TreeNode* tmp = q.front(); // erstes holen
		q.pop();                   // erstes löschen
		tmp->print();              // ausgeben
		if (tmp->getLeft() != nullptr) {
			q.push(tmp->getLeft()); // links hinten anhängen
		}
		if (tmp->getRight() != nullptr) {
			q.push(tmp->getRight()); // rechts hinten anhängen
		}
	}

	printTableSep();

	// Levelorder als 2-3-4-Baum
	if (anker != nullptr) {
		queue<TreeNode*> schwarze;
		queue<int> niveaus;
		int niveau = 0, oldNiveau = 0;

		schwarze.push(anker);
		niveaus.push(niveau);

		while (!schwarze.empty()) {
			bool leftN    = false;
			TreeNode* tmp = schwarze.front(); // erstes rausnehmen
			schwarze.pop();

			oldNiveau = niveau;
			niveau    = niveaus.front(); // niveau rausnehmen
			niveaus.pop();

			if (tmp == nullptr)
				break;

			string nodes = "(";

			TreeNode* left  = tmp->getLeft();
			TreeNode* right = tmp->getRight();

			if (left != nullptr) {
				if (left->getRed()) {
					// falls links existiert
					nodes += to_string(left->getNodePosID()); // id speichern
					leftN = true;

					schwarze.push(left->getLeft()); // da rot ist links und rechts schwarz also anhängen
					niveaus.push(niveau + 1);       // mit niveau + 1

					schwarze.push(left->getRight());
					niveaus.push(niveau + 1);

				} else {
					schwarze.push(left);      // wenn nicht rot dann schwarz und deswegen anhängen
					niveaus.push(niveau + 1); // mit niveau + 1
				}
			}

			nodes += (leftN ? "," : "") + to_string(tmp->getNodePosID()); 

			if (right != nullptr) {
				if (right->getRed()) {
					nodes += "," + to_string(right->getNodePosID());

					schwarze.push(right->getLeft());
					niveaus.push(niveau + 1);

					schwarze.push(right->getRight());
					niveaus.push(niveau + 1);

				} else {
					schwarze.push(right);
					niveaus.push(niveau + 1);
				}
			}

			nodes += ")";

			if (niveau == oldNiveau && niveau != 0) { // niveau hat sich nicht geändert also einfach dahinter ausgeben
				cout << nodes << " ";
			} else {
				cout << endl << "Niveau " << to_string(niveau) << ": " << nodes << " "; // niveau hat sich geändert also neues niveau ausgeben
			}
		}
	}
	cout << endl;

}

bool Tree::rotateTreeRight (TreeNode* a, TreeNode* b) {
	if (a != nullptr && b != nullptr) {
		cout << "RR(" << a->getNodePosID() << "," << b->getNodePosID() << ")" << endl;
	}

	if (a != nullptr && a->getParent() != nullptr && a->getLeft() == b) {
		TreeNode* parent = a->getParent();
		parent->setLeft(a->getRight()); // 1. parent übernimmt links den linken rechten von a
		if (parent->getLeft() != nullptr) { // wenn es den linken teilbaum von a gibt
			parent->getLeft()->setParent(parent); // 2. kriegt der linke knoten als parent den parent von a
		}
		a->setParent(parent->getParent()); // 3. a kriegt als parent den parent vom parent knoten
		a->setRight(parent); // 4. parent kommt rechts vom knoten a
		a->setLeft(b); // 5. knoten b kommt links von a
		if (a->getParent() != nullptr) { // wenn a einen parent hat
			if (a->getParent()->getLeft() == parent) { // wenn parent links von a->parent ist
				a->getParent()->setLeft(a); // 6. dann kommt a links an a->parent 
			} else {
				a->getParent()->setRight(a); // 7. und sonst rechts 
			}
		} else {
			anker = a; // a keinen parent hatte, ist er der anker
		}

		parent->setParent(a); // 8. parent kriegt als parent knoten a
		return true;
	}
	return false;
}

bool Tree::rotateTreeLeft (TreeNode* a, TreeNode* b) {
	if (a != nullptr && b != nullptr) {
		cout << "LR(" << a->getNodePosID() << "," << b->getNodePosID() << ")" << endl;
	}

	if (a != nullptr && a->getParent() != nullptr && a->getRight() == b) {
		TreeNode* parent = a->getParent();
		parent->setRight(a->getLeft()); // 1. parent übernimmt rechts den linken teilbaum von a
		if (parent->getRight() != nullptr) { // wenn es den rechten teilbaum von a gibt
			parent->getRight()->setParent(parent); // 2. kriegt der rechte knoten als parent den parent von a
		}
		a->setParent(parent->getParent()); // 3. a kriegt als parent den parent vom parent knoten
		a->setLeft(parent); // 4. parent kommt links vom knoten a
		a->setRight(b); // 5. knoten b kommt rechts von a
		if (a->getParent() != nullptr) { // wenn a einen parent hat
			if (a->getParent()->getLeft() == parent) { // wenn parent links von a->parent ist
				a->getParent()->setLeft(a); // 6. dann kommt a links an a->parent 
			} else {
				a->getParent()->setRight(a); // 7. und sonst rechts 
			}
		} else {
			anker = a; // a keinen parent hatte, ist er der anker
		}

		parent->setParent(a); // 8. parent kriegt als parent knoten a
		return true;
	}
	return false;
}

bool Tree::is4er (TreeNode* tmp) {
	return
		(tmp != nullptr && tmp->getRed() == false)                    // knoten ist schwarz
		&& (tmp->getLeft() != nullptr && tmp->getLeft()->getRed())    // links ist rot
		&& (tmp->getRight() != nullptr && tmp->getRight()->getRed()); // rechts ist rot
}

void Tree::printTableHead () {
	cout << "ID | Name\t| Alter\t| Einkommen | PLZ   | Pos   | Red   " << endl;
}

void Tree::printTableSep () {
	cout << "---+------------+-------+-----------+-------+-------+-------" << endl;
}
