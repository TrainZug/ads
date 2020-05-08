#include <iostream>
#include "Ring.h"
#include "Ringnode.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

using namespace std;

int main() {
	int result = Catch::Session().run();
	Ring ring;
	bool beendet = false;
	int auswahl = 0;
	string desc, data, suche;
	cout << "Menu" << endl << "================" << endl;
	cout << "1) Backup einfuegen" << endl;
	cout << "2) Backup suchen" << endl;
	cout << "3) Alle Backups ausgeben" << endl;
	do {
		cout << "?> ";
		cin >> auswahl;
		switch (auswahl) {
		case 1:
			cout << "+Neuen Datensatz einfuegen" << endl;
			cout << "Beschreibung ?> ";
			cin >> desc;
			cin.clear();

			cout << "Daten ?> ";
			cin >> data;
			ring.addNode(desc, data);
			cout << "+Ihr Datensatz wurde hinzugefuegt." << endl;
			break;
		case 2:
			cout << "Nach welchen Daten soll gesucht werden?" << endl;
			cout << "?> ";
			cin >> suche;
			if (ring.search(suche)) {
				ring.get(suche);
				cout << "+Gefunden in Backup: " << suche << endl;
			}
			else {
				cout << "+Datensatz konnte nicht gefunden werden" << endl;
			}
			break;
		case 3:
			ring.print();
			break;
		case 0:
			beendet = true;
			cout << "ok" << endl;
			break;
		default:
			break;
		}
	} while (!beendet);
	return 0;
}