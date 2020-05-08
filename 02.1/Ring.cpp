#include "Ring.h"
#include <iostream>
#include <string>
using namespace std;

Ring::Ring()
{
	anker = nullptr;
	AnzahlNodes = 0;
}

void Ring::addNode(string desc, string data)
{
	RingNode* neu = new RingNode(0, desc, data);
	if (AnzahlNodes == 0) { // leer
		anker = neu; // anker zeigt auf age = 0
		neu->setNext(anker);
		AnzahlNodes++;
	}
	else {
		// erstmal alle age von Node +1 machen
		RingNode* tmp = anker;
		for (int i = 0; i < 6 && tmp && (i == 0 || tmp != anker); i++) {
			const int age = tmp->getAge() + 1;
			tmp->setAge(age);
			tmp = tmp->getNext();
		}

		
		if (AnzahlNodes == 1) { // zweite node
			neu->setNext(anker);
			anker->setNext(neu);
			AnzahlNodes++;
		}
		else {
			if (AnzahlNodes > 0 && AnzahlNodes < 6) { // noch nicht voll
				neu->setNext(anker->getNext());
				AnzahlNodes++;
			}
			else { // voll
				RingNode* oldest = anker->getNext(); // wenn voll zeigt anker->next auf älteste Node
				neu->setNext(oldest->getNext());
				delete oldest; // oldest kann weg 
			}
		}
		tmp->setNext(neu);
		anker = neu;
	}
}

bool Ring::search(string search)
{
	RingNode* tmp = anker;
	for (int i = 0; i < 6 && tmp && (i == 0 || tmp != anker); i++) {
		if (tmp->getData() == search) {
			return true;
		}
		tmp = tmp->getNext();
	}
	return false;
}

void Ring::get(string& search) {
	RingNode* tmp = anker;
	for (int i = 0; i < 6 && tmp && (i == 0 || tmp != anker); i++) {
		if (tmp->getData() == search) {
			search = "OldAge " + to_string(tmp->getAge()) + ", Beschreibung: " + tmp->getDescription() + ", Daten: " + tmp->getData();
			break;
		}
		tmp = tmp->getNext();
	}

}

void Ring::print()
{
	RingNode* tmp = anker;
	for (int i = 0; i < 6 && tmp && (i == 0 || tmp != anker); i++) {
		cout << "OldAge: : " << tmp->getAge() << ", Descr: " << tmp->getDescription() << ", Data: " << tmp->getData() << endl;
		cout << "--------------------------" << endl;
		tmp = tmp->getNext();
	}
}
