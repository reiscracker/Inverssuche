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

/*
string Person::ausgabe() {
	cout << setw(25) << "id:" << _id << endl; 
	cout << setw(25) << "Name:" << _name << endl; 
	cout << setw(25) << "Vorname:" << _vorname << endl; 
	cout << setw(25) << "Telefon privat:" << _telefonPrivat << endl; 
	cout << setw(25) << "Telefon dienstlich:" << _telefonDienstlich << endl; 
	cout << setw(25) << "Handy privat:" << _handyPrivat << endl; 
	cout << setw(25) << "Handy dienstlich:" << _handyDienstlich << endl; 
	cout << setw(25) << "Fax privat:" << _faxPrivat << endl; 
	cout << setw(25) << "Fax dienstlich:" << _faxDienstlich << endl; 
}
*/
void Person::addValue(string key, string value) {
	_values.insert(pair<string, string>(key, value));
}

void Person::printValues() {
	map<string, string>::iterator valueIterator = _values.begin();
	for (valueIterator; valueIterator != _values.end(); valueIterator++) {
		/* TODO Formatierung anpassen */
		cout << setw(25) << valueIterator->first << ":" << valueIterator->second << endl;
	}
}

map<string, string>* Person::getValues() {
    
    return &_values;
}