/* 10.01.2014
 * Author: Christine Hecht <s0539719@htw-berlin.de>
 * Author: Simon Arnold <s0539710@htw-berlin.de>
 *
 *
 * Die Klasse Node stellt einen Knotenpunkt im Baum der Telefonnummern da.
 * Sie besitzt eine Liste mit ihren verknüpften Ziffern, sodass sie die Nummer an diese weitergeben kann,
 * bis der der letzten Ziffer einer Nummer entsprechende Knoten gefunden wurde.
 * Weiter kann jede Node einen Zeiger auf ein Person-Objekt halten, zu dem die Telefonnummer gehört.
 */
using namespace std;
#include <list>
#include <string>
#include "person.h"

class Node {

	private:
		Node(int digit);

		const int _digit;
		list<Node> _nextDigits;
		Person* _personWithThisNumber;

		void createNextDigit();

	public:
		Person* processNumber(string number);	
		void setPersonWithThisNumber();
}
