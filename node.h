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
                ~Node();
                /* Die Ziffer, die diese Node enthält */
		const int _digit;
                
                /* Die Node-Objekte mit Ziffern, die von hier aus weiterführen */
		list<Node> _nextDigits;
                
                /* Enthält einen Zeiger auf ein Person-Objekt, falls die Nummer an diesem Punkt 
                   einer Person gehört */
		Person* _personWithThisNumber = NULL;

                /* Fügt ein neues Node-Objekt der Liste der nächsten Ziffern hinzu und gibt 
                   dieses Objekt zurück */
		Node* createNextDigit();

	public:
                /* Fügt eine Nummer zum Baum hinzu und setzt den Zeiger auf den Besitzer der Nummer */
		void addNumber(string number, Person* numberOwner);	
                
                /* Versucht, einen Zeiger auf den Besitzer einer Nummer zu liefern */
                Person* getPerson(string number);
                
                int getDigit();
                    
}
