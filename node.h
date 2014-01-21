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
#ifndef NODE_H
#define	NODE_H

using namespace std;
#include <list>
#include <string>
#include "person.h"
#include <sstream>
//class Person;

class Node {

	private:
                /* Die Ziffer, die diese Node enthält */
		char _digit;
                
                /* Die Node-Objekte mit Ziffern, die von hier aus weiterführen */
		list<Node*> _nextDigits;
                
                /* Enthält einen Zeiger auf ein Person-Objekt, falls die Nummer an diesem Punkt 
                   einer Person gehört */
		Person* _personWithThisNumber;

                /* Findet das Objekt mit der nächsten Ziffer oder legt ein neues an */
		Node* getNextDigit(char digit);

	public:
                Node(char digit);
                ~Node();
                /* Gibt eine Nummer so lang weiter, bis das passende Objekt zu dieser Nummer gefunden wurde. 
                 * Diese Node erhält dann den Zeiger auf das Personen-Objekt */
		void registerNumber(string number, Person* numberOwner);	
                
                /* Versucht, einen Zeiger auf den Besitzer einer Nummer zu liefern */
                Person* getPerson(string number);
                
                char getDigit();
                void setDigit(char newDigit);    
                
                /* Hängt die eigene Ziffer an den sich aufbauenden Baum der Nummern an und gibt den Baum an alle benachbarten
                 * Ziffern weiter. Außerdem wird der Knoten und das Label für den gerade erstellten Knoten und eine evtl anhängende
                 * Person mit dieser Nummer erstellt*/
                void addToGraphString(stringstream& nodes, string numberProgress, stringstream& labelString);
};

#endif