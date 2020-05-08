#include "List.h"

List::List () {
	// Konstruktor für eine leere Liste
	head_tail       = new Node;
	list_size       = 0;
	temp            = false;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
}

List::List (const List & _List) {
	// Konstruktor mit Übergabe einer Liste, die dann kopiert wird.
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	list_form       = _List.list_form;
	head_tail       = new Node;
	list_size       = 0;
	temp            = _List.temp;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
	Node* tmp_node;
	tmp_node = _List.head_tail->next;
	while (tmp_node != _List.head_tail) {
		head_tail->prev             = new Node(tmp_node->key, head_tail->prev->next, head_tail->prev);
		head_tail->prev->prev->next = head_tail->prev;
		list_size++;
		tmp_node = tmp_node->next;
	}
	if (_List.temp)
		delete&_List; // ist die Übergebene Liste eine temporäre Liste? -> aus Operator +
}

List::List (const List* _List) {
	// Konstruktor mit Übergabe einer Liste, die dann kopiert wird.
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	list_form       = _List->list_form;
	head_tail       = new Node;
	list_size       = 0;
	temp            = _List->temp;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
	Node* tmp_node;
	tmp_node = _List->head_tail->next;
	while (tmp_node != _List->head_tail) {
		head_tail->prev             = new Node(tmp_node->key, head_tail->prev->next, head_tail->prev);
		head_tail->prev->prev->next = head_tail->prev;
		list_size++;
		tmp_node = tmp_node->next;
	}
	if (_List->temp)
		delete _List; // ist die Übergebene Liste eine temporäre Liste? -> aus Operator +
}

List::~List () {
	// Dekonstruktor
	// Alle Knoten der Liste müssen gelöscht werden, wenn die Liste gelöscht wird.
	/*
		hier alle Knoten löschen, die im Objekt List allokiert wurden
	*/
	Node* tmp = head_tail->next;

	while (tmp != nullptr && tmp != head_tail) {
		Node* zum_loeschen = tmp;
		tmp                = tmp->next;
		delete zum_loeschen;
	}

	list_size = 0;

	head_tail->next = head_tail;
	head_tail->prev = head_tail;
}

void List::insertFront (int key) {
	// Einfügen eines neuen Knotens am Anfang der Liste
	/*
		Einen neuen Knoten mit dem Schlüsselwert key am Anfang der Liste einfügen
	*/

	Node* node            = new Node(key);
	node->next            = head_tail->next; // neue kriegt 1. als next
	node->prev            = head_tail;       // neue kriegt head als prev
	head_tail->next->prev = node;            // 1. kriegt neue als prev
	head_tail->next       = node;            // neues 1. ist neues
	list_size++;
}

void List::insertFront (List & _List) {
	// Einfügen einer vorhandenen Liste am Anfang
	/*
	Die einzufügenden Knoten werden übernommen (nicht kopiert)
	Die einzufügende Liste _List ist anschließend leer.
	Es darf keine Schleife und kein new benutzt werden.
	*/
	/*
		Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
		Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) übertragen ohne sie zu kopieren!
	*/

	if (_List.head_tail->next != _List.head_tail) {
		// Liste nicht leer

		list_size += _List.list_size;

		_List.head_tail->next->prev = head_tail->prev; // 1
		_List.head_tail->prev->next = head_tail;       // 2

		head_tail->prev->next = _List.head_tail->next; // 3
		head_tail->prev       = _List.head_tail->prev; // 4

		_List.head_tail->next = nullptr;
		_List.head_tail->prev = nullptr;
	}
}

void List::insertFront (List* _List) {
	// Einfügen einer vorhandenen Liste am Anfang
	/*
	Die einzufügenden Knoten werden übernommen (nicht kopiert)
	Die einzufügende Liste _List ist anschließend leer.
	Es darf keine Schleife und kein new benutzt werden.
	*/
	/*
		Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
		Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) übertragen ohne sie zu kopieren!
	*/

	if (_List->head_tail->next != _List->head_tail) {
		// Liste nicht leer

		list_size += _List->list_size;

		_List->head_tail->next->prev = head_tail->prev; // 1
		_List->head_tail->prev->next = head_tail;       // 2

		head_tail->prev->next = _List->head_tail->next; // 3
		head_tail->prev       = _List->head_tail->prev; // 4

		_List->head_tail->next = _List->head_tail;
		_List->head_tail->prev = _List->head_tail;
	}

}

void List::insertBack (int key) {
	// Einfügen eines neuen Knotens am Ende der Liste
	/*
		Einen neuen Knoten mit dem Schlüsselwert key am Ende der Liste einfügen
	*/
	Node* node            = new Node(key);
	node->next            = head_tail;       // neues next ist tail
	node->prev            = head_tail->prev; // neues prev ist letzte node
	head_tail->prev->next = node;            // letzte kriegt neue als next
	head_tail->prev       = node;
	list_size++;
}

void List::insertBack (List & _List) {
	// Einfügen einer vorhandenen Liste am Ende
	/*
	Die einzufügenden Knoten werden übernommen (nicht kopiert)
	Die einzufügende Liste _List ist anschließend leer.
	Es darf keine Schleife und kein new benutzt werden.
	*/
	/*
		Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
		Diese Knoten (koplette Kette) werden an das Ende der Liste (this) angehangen ohne sie zu kopieren!
	*/

	if (_List.head_tail->next != _List.head_tail) {
		list_size += _List.list_size;

		_List.head_tail->next->prev = head_tail;       // 1
		_List.head_tail->prev->next = head_tail->next; // 2

		head_tail->next->prev = _List.head_tail->prev; // 3
		head_tail->next       = _List.head_tail->next; // 4

		_List.head_tail->next = _List.head_tail;
		_List.head_tail->prev = _List.head_tail;
	}

}

void List::insertBack (List* _List) {
	// Einfügen einer vorhandenen Liste am Ende
	/*
	Die einzufügenden Knoten werden übernommen (nicht kopiert)
	Die einzufügende Liste _List ist anschließend leer.
	Es darf keine Schleife und kein new benutzt werden.
	*/
	/*
		Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
		Diese Knoten (koplette Kette) werden an das Ende der Liste (this) angehangen ohne sie zu kopieren!
	*/

	if (_List->head_tail->next != _List->head_tail) {
		list_size += _List->list_size;

		_List->head_tail->next->prev = head_tail;       // 1
		_List->head_tail->prev->next = head_tail->next; // 2

		head_tail->next->prev = _List->head_tail->prev; // 3
		head_tail->next       = _List->head_tail->next; // 4

		_List->head_tail->next = _List->head_tail;
		_List->head_tail->prev = _List->head_tail;
	}
}

bool List::getFront (int & key) {
	// entnehmen des Knotens am Anfang der Liste
	// der Wert wird als Parameter zurückgegeben
	// der Knoten wird entnommen
	/*
		Der Wert des vorderen Schlüsselknotens wird rückgegeben und der Knoten gelöscht.
		Die Methode del(key) darf nicht zum löschen benutzt werden.
	*/
	if (head_tail->next != head_tail->prev) {
		Node* tmp       = head_tail->next;
		key             = tmp->key;
		tmp->next->prev = head_tail;
		head_tail->next = tmp->next;
		delete tmp;
		list_size--;
		return true;
	}
	key = 0;
	return false;
}

bool List::getBack (int & key) {
	// entnehmen des Knotens am Ende der Liste
	// der Wert wird als Parameter zurückgegeben
	// der Knoten wird entnommen
	/*
		Der Wert des letzten Schlüsselknotens wird rückgegeben und der Knoten gelöscht.
		Die Methode del(key) darf nicht zum löschen benutzt werden.
	*/
	if (head_tail->next != head_tail->prev) {
		Node* tmp       = head_tail->prev;
		key             = tmp->key;
		tmp->prev->next = head_tail;
		head_tail->prev = tmp->prev;
		delete tmp;
		list_size--;
		return true;
	}
	key = 0;
	return false;
}

bool List::del (int key) {
	// Löschen eines gegebenen Knotens
	/*
		Löschen des Knotens mit dem Schlüssel key
	*/
	Node* tmp = head_tail->next;
	while (tmp != head_tail) {
		if (tmp->key == key) {
			if (head_tail->next == tmp) {
				// wenn erste node
				head_tail->next = tmp->next;
				tmp->next->prev = head_tail;
			}
			else if (head_tail->prev == tmp) {
				// wenn letzte node
				head_tail->prev = tmp->prev;
				tmp->prev->next = head_tail;
			}
			else {
				// irgendwo in mitte
				Node* tmp2      = tmp;
				tmp->next->prev = tmp->prev;
				tmp->prev->next = tmp2->next;
			}
			list_size--;
			delete tmp;
			return true;
		}
		tmp = tmp->next;
	}
	return false;
}

bool List::search (int key) {
	// suchen eines Knotens
	/*
		suchen ob ein Knoten mit dem Schlüssel key existiert.
	*/
	Node* tmp = head_tail->next;
	while (tmp != head_tail) {
		if (tmp->key == key) { return true; }
		tmp = tmp->next;
	}
	return false;
}

bool List::swap (int key1, int key2) {
	// Vertauschen von zwei Knoten
	// Dabei werden die Zeiger der Knoten und deren Nachbarn verändert.
	/*
		Vertauschen von zwei Knoten mit dem key1 und dem key2
		Es dürfen nicht nur einfach die Schlüssel in den Knoten getauscht werden!
		Die Knoten sind in der Kette umzuhängen.
	*/

	Node* tmp1 = nullptr;
	Node* tmp2 = nullptr;
	Node* tmp  = head_tail->next;
	while (tmp != head_tail) {
		if (tmp->key == key1) {
			tmp1 = tmp;
			break;
		}
		tmp = tmp->next;
	}
	tmp = head_tail->next;
	while (tmp != head_tail) {
		if (tmp->key == key2) {
			tmp2 = tmp;
			break;
		}
		tmp = tmp->next;
	}

	if (tmp1 && tmp2) {
		Node* tmp1_prev = tmp1->prev;
		Node* tmp1_next = tmp1->next;

		Node* tmp2_prev = tmp2->prev;
		Node* tmp2_next = tmp2->next;

		if (tmp1->next == tmp2 || tmp1 == tmp2->next) {
			// nebeneinander

			tmp1->next      = tmp2;
			tmp1->prev      = tmp2_prev;
			tmp2_prev->next = tmp1;

			tmp2->next      = tmp1_next;
			tmp2->prev      = tmp1;
			tmp1_next->prev = tmp2;
		}
		else {
			tmp1->prev       = tmp2_prev; // 1
			tmp1->next       = tmp2_next; // 2
			tmp2->prev->next = tmp1;      // 3
			tmp2->next->prev = tmp1;      // 4

			tmp2->prev      = tmp1_prev;
			tmp2->next      = tmp1_next;
			tmp1_prev->next = tmp2;
			tmp1_next->prev = tmp2;
		}

		return true;
	}
	return false;

}

int List::size (void) {
	// Rückgabe der Knoten in der Liste mit O(1)
	/*
		Anzahl der Knoten in der Liste zurückgeben.
	*/

	return list_size;
}

bool List::test (void) {
	// Testmethode: die Methode durchläuft die Liste vom Anfang bis zum Ende und zurück
	// Es werden dabei die Anzahl der Knoten gezählt.
	// Stimmt die Anzahl der Knoten überein liefert die Methode true
	Node* tmp  = head_tail->next;
	int i_next = 0, i_prev = 0;
	while (tmp != head_tail) {
		tmp = tmp->next;
		if (i_next > list_size)
			return false;
		i_next++;
	}
	if (i_next != list_size)
		return false;
	tmp = head_tail->prev;
	while (tmp != head_tail) {
		tmp = tmp->prev;
		if (i_prev > list_size)
			return false;
		i_prev++;
	}
	return i_prev == i_next;
}

List & List::operator = (const List & _List) {
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == &_List)
		return *this; //  !! keine Aktion notwendig
	list_form = _List.list_form;
	Node* tmp_node;
	if (list_size) {
		Node* tmp_del;
		tmp_node = head_tail->next;
		while (tmp_node != head_tail) // Alle eventuell vorhandenen Knoten in this löschen
		{
			tmp_del  = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		list_size       = 0;
		head_tail->next = head_tail;
		head_tail->prev = head_tail;
	}
	tmp_node = _List.head_tail->next; // Die Listen-Knotenwerte werden kopiert
	while (tmp_node != _List.head_tail) {
		insertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (_List.temp)
		delete&_List; // ist die Übergebene Liste eine temporäre Liste? -> aus Operator +
	return *this;
}

List & List::operator = (const List* _List) {
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == _List)
		return *this; //  !! keine Aktion notwendig
	list_form = _List->list_form;
	Node* tmp_node;
	if (list_size) {
		Node* tmp_del;
		tmp_node = head_tail->next;
		while (tmp_node != head_tail) // Alle eventuell vorhandenen Knoten in this löschen
		{
			tmp_del  = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		list_size       = 0;
		head_tail->next = head_tail;
		head_tail->prev = head_tail;
	}
	tmp_node = _List->head_tail->next;
	while (tmp_node != _List->head_tail) // Die Listen-Knotenwerte werden kopiert
	{
		insertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (_List->temp)
		delete _List; // ist die Übergebene Liste eine temporäre Liste? -> aus Operator +
	return *this;
}

List & List::operator + (const List & List_Append) {
	// Die Methode +
	// Es werden zwei Listen aneinander gehangen.
	// Dabei werden beide Ursprungslisten nicht verändert. Es entsteht eine neue Ergebnisliste.
	Node* tmp_node;
	List* tmp;
	if (temp) {
		// this ist eine temporäre Liste und kann verändert werden
		tmp = this;
	}
	else {
		tmp       = new List(this); // this ist keine temporäre Liste -> Kopie erzeugen
		tmp->temp = true;           // Merker setzten, dass es sich um eine temporäre Liste handelt
	}
	if (List_Append.list_size) {
		// anhängen der übergebenen Liste an tmp
		tmp_node = List_Append.head_tail->next;
		while (tmp_node != List_Append.head_tail) {
			tmp->insertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append.temp)
		delete&List_Append; // wurde eine temporäre Liste übergeben, dann wird diese gelöscht						
	return *tmp;
}

List & List::operator + (const List* List_Append) {
	// Die Methode +
	// Es werden zwei Listen aneinander gehangen.
	// Dabei werden beide Ursprungslisten nicht verändert. Es entsteht eine neue Ergebnisliste.
	Node* tmp_node;
	List* tmp;
	if (temp) {
		// this ist eine temporäre Liste und kann verändert werden
		tmp = this;
	}
	else {
		tmp       = new List(this); // this ist keine temporäre Liste -> Kopie erzeugen
		tmp->temp = true;           // Merker setzten, dass es sich um eine temporäre Liste handelt
	}
	if (List_Append->list_size) {
		// anhängen der übergebenen Liste an tmp
		tmp_node = List_Append->head_tail->next;
		while (tmp_node != List_Append->head_tail) {
			tmp->insertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append->temp)
		delete List_Append; // wurde eine temporäre Liste übergeben, dann wird diese gelöscht					
	return *tmp;
}

void List::format (const std::string & start, const std::string & zwischen, const std::string & ende) {
	// Setzen des Formates für die Ausgabesteuerung der Liste bei cout
	// das Format wird für den überladenen Operator << verwendet
	list_form.start    = start;
	list_form.zwischen = zwischen;
	list_form.ende     = ende;
}

std::ostream & operator<< (std::ostream & stream, List const & Liste) {
	// Ausgabe der Liste mit cout
	stream << Liste.list_form.start;
	for (Node* tmp = Liste.head_tail->next; tmp != Liste.head_tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste.head_tail ? Liste.list_form.ende : Liste.list_form.zwischen);
	if (Liste.temp)
		delete&Liste; // wurde eine temporäre Liste übergeben, dann wird diese gelöscht
	return stream;
}

std::ostream & operator << (std::ostream & stream, List const* Liste) {
	// Ausgabe der Liste mit cout
	stream << Liste->list_form.start;
	for (Node* tmp = Liste->head_tail->next; tmp != Liste->head_tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste->head_tail ? Liste->list_form.ende : Liste->list_form.zwischen);
	if (Liste->temp)
		delete Liste; // wurde eine temporäre Liste übergeben, dann wird diese gelöscht
	return stream;
}
