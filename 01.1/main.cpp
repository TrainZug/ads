#include <iostream>
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "List.h"
using namespace std;

int main(void)
{
	int result = Catch::Session().run();
	int i;
	List MyList;

	for (i = 0; i < 10; i++) {
		MyList.insertFront(i + 1);
		MyList.insertBack(i + 100);
	}

	cout << MyList;

	cout << "100: " << (MyList.search(100) ? "gefunden" : "nicht gefunden") << endl;
	cout << "99: " << (MyList.search(99) ? "gefunden" : "nicht gefunden") << endl << endl;

	while (MyList.getBack(i))
		cout << i << " ";

	cout << endl << endl;

	List MyList1, MyList2, MyList3;
	List* MyList_dyn = new List;

	for (i = 0; i < 10; i++) {
		MyList1.insertFront(i + 1);
		MyList2.insertBack(i + 100);
	}

	MyList1.format("MyList1\n<<", ", ", ">>\n\n");
	cout << MyList1;

	MyList_dyn->format("MyList_dyn\n<<", ", ", ">>\n\n");
	MyList_dyn->insertFront(-111);
	cout << MyList_dyn;

	MyList2.format("MyList2\n<<", ", ", ">>\n\n");
	cout << MyList2;

	MyList3 = MyList1 + MyList_dyn + MyList2;

	delete MyList_dyn;

	cout << "Groesse von MyList3: " << MyList3.size() << endl << endl;

	MyList3.format("MyList3\n<<", ", ", ">>\n\n");
	cout << MyList3 << endl;

	MyList3.swap(8, 103);
	cout << MyList3;

	MyList3.swap(100, -111);

	cout << MyList3;

	if (MyList3.test())
		cout << "MyList3: Zeiger OK\n\n";
	else
		cout << "MyList3: Zeiger ******Error\n\n";

	// Eiegene Tests
	
	// Leere Liste anh�ngen
	List test;
	int vorher = MyList3.size();
	MyList3.insertFront(test);
	int nachher = MyList3.size();
	if (vorher != nachher) {
		cout << "l�nge gr��er geworden obwohl liste leer ist" << endl;;
	}

	// in Leerer Liste swapen
	test.swap(1, 2);

	// nur eins finden beim swap
	test.insertFront(1);
	test.swap(1, 2);


	Node* tmp = get_anker(test);
	if (tmp->next->key != 1) {
		cout << "fehler" << endl;
	}

	test.insertFront(2);
	if (tmp->next->key != 2) {
		cout << "insertfron(2) fehler" << endl;
	}

	// swap testen
	test.swap(1, 2);
	if (tmp->next->key != 1 || tmp->next->next->key != 2) {
		cout << "swap(1,2) fehler" << endl;
	}

	// size beim l�schen testen
	vorher = test.size();
	// nicht vorhandene node l�schen
	test.del(3);
	nachher = test.size();
	if (vorher != nachher) {
		cout << "del(3) fehler" << endl;
	}
	test.del(2);
	if (test.size() != 1) {
		cout << "del(2) fehler" << endl;
	}

	system("PAUSE");
	return 0;
}
