/* 08.01.2014
 * Author: Christine Hecht <s	@htw-berlin.de>
 * Author: Simon Arnold <s0539710@htw-berlin.de>
 *
 * Objekte der Klasse Person enthalten genau eine Person mit ihren Telefonnummern.
 * Diese Objekte werden im Hauptprogramm zu einer Liste verknüpft, um die eingelesenen Personen zu speichern.
*/
using namespace std;
#include <person.h>
#include <iostream>
#include <iomanip>

/*
Person::Person(const string const *personenDaten) :
	_id(*personenDaten[0]), _name(*personenDaten[1]), _vorname(*personenDaten[2]), _telefonPrivat(*personenDaten[3]),
	_telefonDienstlich(*personenDaten[4]), _handyPrivat(*personenDaten[5]), _handyDienstlich(*personenDaten[6]),
	_faxPrivat(*personenDaten[7]), _faxDienstlich(*personenDaten[8]) {

}
 
Person::Person(int id, string name, string vorname, string telefonPrivat,
		string telefonDienstlich, string handyPrivat, string handyDienstlich,
		string faxPrivat, string faxDienstlich) :
		_name(name), _vorname(vorname), _telefonPrivat(telefonPrivat),
		_telefonDienstlich(telefonDienstlich),	_handyPrivat(handyPrivat),
		_handyDienstlich(handyDienstlich), _faxPrivat(faxPrivat), _faxDienstlich(faxDienstlich) {

}

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
void Person::addValue(string identifier, string value) {
	_values.insert(pair<string, string>(identifier, value));	
}

void Person::printValues() {
	map<string, string>::iterator valueIterator = _values.begin();
	for (valueIterator; valueIterator != _values.end(); valueIterator++) {
		cout << setw(25) << valueIterator->first << ":" << valueIterator->second << endl;
	}
}
