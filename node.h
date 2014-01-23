/* 10.01.2014
 * Author: Christine Hecht <s0539719@htw-berlin.de>
 * Author: Simon Arnold <s0539710@htw-berlin.de>
 *
 *
 * Die Klasse Node stellt einen Knotenpunkt im Baum der Telefonnummern da und enthält eine Ziffer.
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

class Node {

	private:
		char _digit;
		list<Node*> _nextDigits;
		Person* _personWithThisNumber;

                /* Findet das Objekt mit der nächsten Ziffer oder legt ein neues an.
                 *      @param  digit Ziffer, für die das nächste Objekt gefunden/angelegt werden soll
                 *      @returns Zeiger auf gefundenes/angelegtes Objekt */
		Node* getNextDigit(char digit);

	public:
                /* @param digit Ziffer, die das Objekt besitzen soll */
                Node(char digit);
                ~Node();
                
                /* Gibt eine Nummer so lang weiter, bis das passende Objekt zu dieser Nummer gefunden wurde. 
                 * Dieses Objekt der Klasse Node speichert dann den Zeiger auf das Personen-Objekt numberOwner 
                 *      @param number Nummer, für die das entsprechende Objekt gefunden werden soll
                 *      @param numberOwner Objekt der Klasse Person, das dann mit dem gefundenen Node-Objekt
                 *                          verknüft werden soll
                 *      @exception runtime_error Fehler, falls die Ziffer dieses Objektes nicht zur aktuell erwarteten
                 *                              Ziffer der Telefonnummer passen sollte.
                 */
		void registerNumber(string number, Person* numberOwner);	
                
                /* Versucht, die mit einer Nummer verbundene Person zu liefern. Dabei wird die Nummer so lang
                 * weitergereicht, bis das passende Objekt der Klasse Node gefunden wurde oder ein Fehler auftritt
                        @param number Nummer, für die eine Person gefunden werden soll
                        @returns Person-Objekt für dieser Nummer
                 *      @exception runtime_error Fehler, falls die Ziffer dieses Objektes nicht zur aktuell erwarteten
                 *                              Ziffer der Telefonnummer passen sollte.
                 *      @exception runtime_error Fehler, falls für die angegebene Telefonnummer kein Person-Objekt existiert
                 *      @exception runtime_error Fehler, falls die angegebene Telefonnummer im Baum nicht existiert
                 */
                Person* getPerson(string number);
                
                /* @returns digit Ziffer, die dieses Objekt besitzt */
                char getDigit();
                
                void setDigit(char newDigit);    
                
                /* Hängt die eigene Ziffer an den sich aufbauenden String der Nummern an und gibt die Strings 
                 * an alle benachbarten Ziffern weiter. Außerdem wird der Knoten und das Label für den gerade 
                 * hinzugefügten Knoten und eine evtl anhängende Person mit dieser Nummer erstellt
                 *      @param nodes String, in dem die Verknüpfungen der Knoten in der DOT-Sprache beschrieben werden
                 *      @param numberProgress Ziffernverlauf vom Startknoten zu diesem
                 *      @param labelString String, in dem die Label der einzelnen Knoten in der DOT-Sprache beschrieben werden
                 */
                void addToGraphString(stringstream& nodes, string numberProgress, stringstream& labelString);
};

#endif