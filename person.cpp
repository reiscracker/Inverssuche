/* 08.01.2014
 * Author: Christine Hecht <s0539719@htw-berlin.de>
 * Author: Simon Arnold <s0539710@htw-berlin.de>
 *
 * Objekte der Klasse Person enthalten genau eine Person mit ihren Telefonnummern.
 * Diese Objekte werden im Hauptprogramm zu einer Liste verknüpft, um die eingelesenen Personen zu speichern.
*/
using namespace std;
#include "person.h"
#include <iostream>
#include <iomanip>

void Person::addValue(string key, string value) {
	_values.insert(pair<string, string>(key, value));
}

void Person::printValues() {
	map<string, string>::iterator valueIterator = _values.begin();
	for (valueIterator; valueIterator != _values.end(); valueIterator++) {
		cout << setw(25) << valueIterator->first << ":";
                cout << setw(10) << valueIterator->second << endl;
	}
}

map<string, string>* Person::getValues() {
    return &_values;
}