#define CATCH_CONFIG_RUNNER
#include <iostream>
#include <fstream>
#include "Tree.h"
#include "catch.h"

using namespace std;

void printMenu ();
void readCSV (Tree & tree);

int main () {

	int result = Catch::Session().run();
	Tree tree;
	string eingabe = "", name;
	int alter, plz, zu_loeschen;;
	double einkommen;

	do {
		printMenu();
		cout << "?> ";
		cin >> eingabe;
		if (eingabe == "1") {

			cout << "Bitte geben Sie den Datensatz ein" << endl;
			cout << "Name ?> ";
			cin >> name;
			cout << "Alter ?> ";
			cin >> alter;
			cout << "Einkommen ?> ";
			cin >> einkommen;
			cout << "PLZ ?> ";
			cin >> plz;
			tree.addNode(name, alter, einkommen, plz);
			cout << "+ Ihr Datensatz wurde eingefuegt" << endl;
		} else if (eingabe == "2") {
			cout << "2 + Moechten Sie die Daten aus der Datei \"ExportZielanalyse.csv\" importieren (j/n) ?>";
			cin >> eingabe;
			if (eingabe == "j") {
				readCSV(tree);
				cout << "Daten wurden dem Baum hinzugefuegt" << endl;
			}
		} else if (eingabe == "3") {
			cout << "+ Bitte geben Sie den zu loeschenden Datensatz an" << endl;
			cout << "PosID ?> ";
			cin >> zu_loeschen;
			tree.deleteNode(zu_loeschen);
			cout << "+ Datensatz wurde geloescht." << endl;
		} else if (eingabe == "4") {
			cout << "+ Bitte geben Sie den zu suchenden Datensatz an" << endl;
			cout << "Name ?> ";
			cin >> name;
			tree.searchNode(name);
		} else if (eingabe == "5") {
			tree.printAll();
		} else if (eingabe == "0") {
			cout << "ok" << endl;
			break;
		} else {
			cout << "Unbekannte Eingabe..." << endl;
		}
	}
	while (true);

	system("PAUSE");

	return 0;
}

void printMenu () {
	cout << "Menue:" << endl;
	cout << "1) Datensatz einfuegen, manuell" << endl;
	cout << "2) Datensatz einfuegen, csv" << endl;
	cout << "3) Datensatz löschen" << endl;
	cout << "4) Suchen" << endl;
	cout << "5) Datenstruktur anzeigen" << endl;
}

void readCSV (Tree & tree) {
	fstream f("ExportZielanalyse.csv");
	if (!f.is_open()) {
		cout << "Fehler beim oeffnen von ExportZielanalyse.csv" << endl;
		return;
	}
	string name, s;
	int plz, alter;
	double einkommen;
	char sep = ';';

	while (!f.eof()) {

		s = "";
		getline(f, s, sep);
		if (s.empty())
			break;
		name = s;
		getline(f, s, sep);
		alter = stoi(s);
		getline(f, s, sep);
		einkommen = stod(s);
		getline(f, s, '\n');
		plz = stoi(s);
		tree.addNode(name, alter, einkommen, plz);
	}
	f.close();

}
