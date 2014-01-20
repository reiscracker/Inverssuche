/* 08.01.2014
 * Author: Christine Hecht <s0539719@htw-berlin.de>
 * Author: Simon Arnold <s0539710@htw-berlin.de>
 *
 * Objekte der Klasse Person enthalten genau eine Person mit ihren Telefonnummern.
 * Diese Objekte werden im Hauptprogramm zu einer Liste verknüpft, um die eingelesenen Personen zu speichern.
*/
#ifndef PERSON_H
#define	PERSON_H


using namespace std;
#include <string>
#include <map>

class Person {
	private:
		map<string, string> _values;

	public:
		void addValue(string key, string value);
		void printValues();	
                string getName();
};

#endif