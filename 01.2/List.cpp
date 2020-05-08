#include "List.h"
template <class T>
List<T>::List()
{
	// Konstruktor f�r eine leere Liste
	head_tail = new Node<T>;
	list_size = 0;
	temp = false;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
}
template <class T>
List<T>::List(const List<T>& _List)
{
	// Konstruktor mit �bergabe einer Liste, die dann kopiert wird.
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	list_form = _List.list_form;
	head_tail = new Node<T>;
	list_size = 0;
	temp = _List.temp;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
	Node<T>* tmp_node;
	tmp_node = _List.head_tail->next;
	while (tmp_node != _List.head_tail)
	{
		head_tail->prev = new Node<T>(tmp_node->key, head_tail->prev->next, head_tail->prev);
		head_tail->prev->prev->next = head_tail->prev;
		list_size++;
		tmp_node = tmp_node->next;
	}
	if (_List.temp) delete& _List;		// ist die �bergebene Liste eine tempor�re Liste? -> aus Operator +
}
template <class T>
List<T>::List(const List<T>* _List)
{
	// Konstruktor mit �bergabe einer Liste, die dann kopiert wird.
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	list_form = _List->list_form;
	head_tail = new Node<T>;
	list_size = 0;
	temp = _List->temp;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
	Node<T>* tmp_node;
	tmp_node = _List->head_tail->next;
	while (tmp_node != _List->head_tail)
	{
		head_tail->prev = new Node<T>(tmp_node->key, head_tail->prev->next, head_tail->prev);
		head_tail->prev->prev->next = head_tail->prev;
		list_size++;
		tmp_node = tmp_node->next;
	}
	if (_List->temp) delete _List;		// ist die �bergebene Liste eine tempor�re Liste? -> aus Operator +
}
template <class T>
List<T>::~List()
{
	// Dekonstruktor
	// Alle Knoten der Liste m�ssen gel�scht werden, wenn die Liste gel�scht wird.
/*
	hier alle Knoten l�schen, die im Objekt List allokiert wurden
*/
	Node<T>* tmp = head_tail->next;

	while (tmp != nullptr && tmp != head_tail) {
		Node<T>* zum_loeschen = tmp;
		tmp = tmp->next;
		delete zum_loeschen;

	}

	list_size = 0;

	head_tail->next = head_tail;
	head_tail->prev = head_tail;
}
template <class T>
void List<T>::insertFront(T key)
{
	// Einf�gen eines neuen Knotens am Anfang der Liste
/*
	Einen neuen Knoten mit dem Schl�sselwert key am Anfang der Liste einf�gen
*/


	Node<T>* node = new Node<T>(key);
	node->next = head_tail->next; // neue kriegt 1. als next
	node->prev = head_tail; // neue kriegt head als prev
	head_tail->next->prev = node; // 1. kriegt neue als prev
	head_tail->next = node; // neues 1. ist neues
	list_size++;
}
template <class T>
void List<T>::insertFront(List<T>& _List)
{
	// Einf�gen einer vorhandenen Liste am Anfang
	/*
	Die einzuf�genden Knoten werden �bernommen (nicht kopiert)
	Die einzuf�gende Liste _List ist anschlie�end leer.
	Es darf keine Schleife und kein new benutzt werden.
	*/
	/*
		Es wird ein Objekt �bergeben in dem Knoten vorhanden sein k�nnen.
		Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) �bertragen ohne sie zu kopieren!
	*/
	if (_List.head_tail->next != _List.head_tail) {

		list_size += _List.list_size;

		_List.head_tail->next->prev = head_tail; // 1
		_List.head_tail->prev->next = head_tail->next; // 2

		head_tail->next->prev = _List.head_tail->prev; // 3
		head_tail->next = _List.head_tail->next; // 4


		_List.head_tail->next = _List.head_tail;
		_List.head_tail->prev = _List.head_tail;
	}

}
template <class T>
void List<T>::insertFront(List<T>* _List)
{
	// Einf�gen einer vorhandenen Liste am Anfang
	/*
	Die einzuf�genden Knoten werden �bernommen (nicht kopiert)
	Die einzuf�gende Liste _List ist anschlie�end leer.
	Es darf keine Schleife und kein new benutzt werden.
	*/
	/*
		Es wird ein Objekt �bergeben in dem Knoten vorhanden sein k�nnen.
		Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) �bertragen ohne sie zu kopieren!
	*/


	if (_List->head_tail->next != _List->head_tail) {

		list_size += _List->list_size;

		_List->head_tail->next->prev = head_tail; // 1
		_List->head_tail->prev->next = head_tail->next; // 2

		head_tail->next->prev = _List->head_tail->prev; // 3
		head_tail->next = _List->head_tail->next; // 4


		_List->head_tail->next = _List->head_tail;
		_List->head_tail->prev = _List->head_tail;
	}
}
template <class T>
void List<T>::insertBack(T key)
{
	// Einf�gen eines neuen Knotens am Ende der Liste
/*
	Einen neuen Knoten mit dem Schl�sselwert key am Ende der Liste einf�gen
*/
	Node<T>* node = new Node<T>(key);
	node->next = head_tail; // neues next ist tail
	node->prev = head_tail->prev; // neues prev ist letzte node
	head_tail->prev->next = node; // letzte kriegt neue als next
	head_tail->prev = node;
	list_size++;
}
template <class T>
void List<T>::insertBack(List<T>& _List)
{
	// Einf�gen einer vorhandenen Liste am Ende
	/*
	Die einzuf�genden Knoten werden �bernommen (nicht kopiert)
	Die einzuf�gende Liste _List ist anschlie�end leer.
	Es darf keine Schleife und kein new benutzt werden.
	*/
	/*
		Es wird ein Objekt �bergeben in dem Knoten vorhanden sein k�nnen.
		Diese Knoten (koplette Kette) werden an das Ende der Liste (this) angehangen ohne sie zu kopieren!
	*/
	if (_List.head_tail->next != _List.head_tail) { // Liste nicht leer

		list_size += _List.list_size;

		_List.head_tail->next->prev = head_tail->prev; // 1
		_List.head_tail->prev->next = head_tail; // 2

		head_tail->prev->next = _List.head_tail->next; // 3
		head_tail->prev = _List.head_tail->prev; // 4


		_List.head_tail->next = nullptr;
		_List.head_tail->prev = nullptr;
	}

}
template <class T>
void List<T>::insertBack(List<T>* _List)
{
	// Einf�gen einer vorhandenen Liste am Ende
	/*
	Die einzuf�genden Knoten werden �bernommen (nicht kopiert)
	Die einzuf�gende Liste _List ist anschlie�end leer.
	Es darf keine Schleife und kein new benutzt werden.
	*/
	/*
		Es wird ein Objekt �bergeben in dem Knoten vorhanden sein k�nnen.
		Diese Knoten (koplette Kette) werden an das Ende der Liste (this) angehangen ohne sie zu kopieren!
	*/

	if (_List->head_tail->next != _List->head_tail) { // Liste nicht leer

		list_size += _List->list_size;

		_List->head_tail->next->prev = head_tail->prev; // 1
		_List->head_tail->prev->next = head_tail; // 2

		head_tail->prev->next = _List->head_tail->next; // 3
		head_tail->prev = _List->head_tail->prev; // 4


		_List->head_tail->next = _List->head_tail;
		_List->head_tail->prev = _List->head_tail;
	}
}
template <class T>
bool List<T>::getFront(T& key)
{
	// entnehmen des Knotens am Anfang der Liste
	// der Wert wird als Parameter zur�ckgegeben
	// der Knoten wird entnommen
/*
	Der Wert des vorderen Schl�sselknotens wird r�ckgegeben und der Knoten gel�scht.
	Die Methode del(key) darf nicht zum l�schen benutzt werden.
*/
	if (head_tail->next != head_tail->prev) {
		Node<T>* tmp = head_tail->next;
		key = tmp->key;
		tmp->next->prev = head_tail;
		head_tail->next = tmp->next;
		delete tmp;
		list_size--;
		return key;
	}
}
template <class T>
bool List<T>::getBack(T& key)
{	// entnehmen des Knotens am Ende der Liste
	// der Wert wird als Parameter zur�ckgegeben
	// der Knoten wird entnommen
/*
	Der Wert des letzten Schl�sselknotens wird r�ckgegeben und der Knoten gel�scht.
	Die Methode del(key) darf nicht zum l�schen benutzt werden.
*/
	if (head_tail->next != head_tail->prev) {
		Node<T>* tmp = head_tail->prev;
		key = tmp->key;
		tmp->prev->next = head_tail;
		head_tail->prev = tmp->prev;
		delete tmp;
		list_size--;
		return key;
	}
	return 0;
}
template <class T>
bool List<T>::del(T key)
{
	// L�schen eines gegebenen Knotens
/*
	L�schen des Knotens mit dem Schl�ssel key
*/
	Node<T>* tmp = head_tail->next;
	while (tmp != head_tail) {
		if (tmp->key == key) {
			if (head_tail->next == tmp) { // wenn erste node
				head_tail->next = tmp->next;
				tmp->next->prev = head_tail;
			}
			else if (head_tail->prev == tmp) { // wenn letzte node
				head_tail->prev = tmp->prev;
				tmp->prev->next = head_tail;
			}
			else { // irgendwo in mitte
				Node<T>* tmp2 = tmp;
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
template <class T>
bool List<T>::search(T key)
{
	// suchen eines Knotens
/*
	suchen ob ein Knoten mit dem Schl�ssel key existiert.
*/
	Node<T>* tmp = head_tail->next;
	while (tmp != head_tail) {
		if (tmp->key == key) {
			return true;
		}
		tmp = tmp->next;
	}
	return false;
}
template <class T>
bool List<T>::swap(T key1, T key2)
{
	// Vertauschen von zwei Knoten
	// Dabei werden die Zeiger der Knoten und deren Nachbarn ver�ndert.
/*
	Vertauschen von zwei Knoten mit dem key1 und dem key2
	Es d�rfen nicht nur einfach die Schl�ssel in den Knoten getauscht werden!
	Die Knoten sind in der Kette umzuh�ngen.
*/

	Node<T>* tmp1 = nullptr;
	Node<T>* tmp2 = nullptr;
	Node<T>* tmp = head_tail->next;
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

		Node<T>* tmp1_prev = tmp1->prev;
		Node<T>* tmp1_next = tmp1->next;

		Node<T>* tmp2_prev = tmp2->prev;
		Node<T>* tmp2_next = tmp2->next;

		if (tmp1->next == tmp2 || tmp1 == tmp2->next) { // nebeneinander

			tmp1->next = tmp2;
			tmp1->prev = tmp2_prev;
			tmp2_prev->next = tmp1;

			tmp2->next = tmp1_next;
			tmp2->prev = tmp1;
			tmp1_next->prev = tmp2;

		}
		else {

			tmp1->prev = tmp2_prev; // 1
			tmp1->next = tmp2_next; // 2
			tmp2->prev->next = tmp1; // 3
			tmp2->next->prev = tmp1; // 4

			tmp2->prev = tmp1_prev;
			tmp2->next = tmp1_next;
			tmp1_prev->next = tmp2;
			tmp1_next->prev = tmp2;
		}




		return true;
	}
	return false;

}
template <class T>
int List<T>::size(void)
{
	// R�ckgabe der Knoten in der Liste mit O(1)
/*
	Anzahl der Knoten in der Liste zur�ckgeben.
*/

	return list_size;
}
template <class T>
bool List<T>::test(void)
{
	// Testmethode: die Methode durchl�uft die Liste vom Anfang bis zum Ende und zur�ck
	// Es werden dabei die Anzahl der Knoten gez�hlt.
	// Stimmt die Anzahl der Knoten �berein liefert die Methode true
	Node<T>* tmp = head_tail->next;
	int i_next = 0, i_prev = 0;
	while (tmp != head_tail) {
		tmp = tmp->next;
		if (i_next > list_size) return false;
		i_next++;
	}
	if (i_next != list_size) return false;
	tmp = head_tail->prev;
	while (tmp != head_tail) {
		tmp = tmp->prev;
		if (i_prev > list_size) return false;
		i_prev++;
	}
	return i_prev == i_next;
}
template <class T>
List<T>& List<T>::operator = (const List<T>& _List)
{
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == &_List) return *this;		//  !! keine Aktion notwendig
	list_form = _List.list_form;
	Node<T>* tmp_node;
	if (list_size)
	{
		Node<T>* tmp_del;
		tmp_node = head_tail->next;
		while (tmp_node != head_tail)		// Alle eventuell vorhandenen Knoten in this l�schen
		{
			tmp_del = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		list_size = 0;
		head_tail->next = head_tail;
		head_tail->prev = head_tail;
	}
	tmp_node = _List.head_tail->next;		// Die Listen-Knotenwerte werden kopiert
	while (tmp_node != _List.head_tail)
	{
		insertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (_List.temp) delete& _List;			// ist die �bergebene Liste eine tempor�re Liste? -> aus Operator +
	return *this;
}
template <class T>
List<T>& List<T>::operator = (const List<T>* _List)
{
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == _List) return *this;		//  !! keine Aktion notwendig
	list_form = _List->list_form;
	Node<T>* tmp_node;
	if (list_size)
	{
		Node<T>* tmp_del;
		tmp_node = head_tail->next;
		while (tmp_node != head_tail)		// Alle eventuell vorhandenen Knoten in this l�schen
		{
			tmp_del = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		list_size = 0;
		head_tail->next = head_tail;
		head_tail->prev = head_tail;
	}
	tmp_node = _List->head_tail->next;
	while (tmp_node != _List->head_tail)	// Die Listen-Knotenwerte werden kopiert
	{
		insertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (_List->temp) delete _List;			// ist die �bergebene Liste eine tempor�re Liste? -> aus Operator +
	return *this;
}
template <class T>
List<T>& List<T>::operator + (const List<T>& List_Append)
{
	// Die Methode +
	// Es werden zwei Listen aneinander gehangen.
	// Dabei werden beide Ursprungslisten nicht ver�ndert. Es entsteht eine neue Ergebnisliste.
	Node<T>* tmp_node;
	List<T>* tmp;
	if (temp) {										// this ist eine tempor�re Liste und kann ver�ndert werden
		tmp = this;
	}
	else {
		tmp = new List(this);						// this ist keine tempor�re Liste -> Kopie erzeugen
		tmp->temp = true;							// Merker setzten, dass es sich um eine tempor�re Liste handelt
	}
	if (List_Append.list_size) {					// anh�ngen der �bergebenen Liste an tmp
		tmp_node = List_Append.head_tail->next;
		while (tmp_node != List_Append.head_tail) {
			tmp->insertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append.temp) delete& List_Append;		// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht						
	return *tmp;
}
template <class T>
List<T>& List<T>::operator + (const List<T>* List_Append)
{
	// Die Methode +
	// Es werden zwei Listen aneinander gehangen.
	// Dabei werden beide Ursprungslisten nicht ver�ndert. Es entsteht eine neue Ergebnisliste.
	Node<T>* tmp_node;
	List<T>* tmp;
	if (temp) {										// this ist eine tempor�re Liste und kann ver�ndert werden
		tmp = this;
	}
	else {
		tmp = new List(this);						// this ist keine tempor�re Liste -> Kopie erzeugen
		tmp->temp = true;							// Merker setzten, dass es sich um eine tempor�re Liste handelt
	}
	if (List_Append->list_size) {					// anh�ngen der �bergebenen Liste an tmp
		tmp_node = List_Append->head_tail->next;
		while (tmp_node != List_Append->head_tail) {
			tmp->insertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append->temp) delete List_Append;		// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht					
	return *tmp;
}
template <class T>
void List<T>::format(const std::string& start, const std::string& zwischen, const std::string& ende)
{
	// Setzen des Formates f�r die Ausgabesteuerung der Liste bei cout
	// das Format wird f�r den �berladenen Operator << verwendet
	list_form.start = start;
	list_form.zwischen = zwischen;
	list_form.ende = ende;
}
template <class Tf>
std::ostream& operator<<(std::ostream& stream, List<Tf> const& Liste)
{
	// Ausgabe der Liste mit cout
	stream << Liste.list_form.start;
	for (Node<Tf>* tmp = Liste.head_tail->next; tmp != Liste.head_tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste.head_tail ? Liste.list_form.ende : Liste.list_form.zwischen);
	if (Liste.temp) delete& Liste;			// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht
	return stream;
}
template <class Tf>
std::ostream& operator << (std::ostream& stream, List<Tf> const* Liste)
{
	// Ausgabe der Liste mit cout
	stream << Liste->list_form.start;
	for (Node<Tf>* tmp = Liste->head_tail->next; tmp != Liste->head_tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste->head_tail ? Liste->list_form.ende : Liste->list_form.zwischen);
	if (Liste->temp) delete Liste;			// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht
	return stream;
}
