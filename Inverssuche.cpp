/* 08.01.2014
 * Author: Christine Hecht <s	@htw-berlin.de>
 * Author: Simon Arnold <s0539710@htw-berlin.de>
 *
 * Dieses Programm realisiert eine Inverssuche durch einen Baum von Telefonnummern. Eine Liste von Nummern wird
 * aus einer Datei eingelesen, die Nummern werden anschließend in einen Indexbaum gespeichert. Es ist dann möglich,
 * anhand einer Telefonnummer Name und weitere Telefonnummern des Besitzers der Nummer herauszufinden.
 * */
using namespace std;
#include <list>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "person.h"

list<Person> createListFromFile(string filename);
vector<string> readValuesFromLine(string line);

int main(int argc, const char* argv[]) {
	cout << "Programm gestartet" << endl;
	
	/* Liste in der die Personen aus der Datei gespeichert werden */
	list<Person> personen;

	/* Es muss mindestens eine Datei angegeben sein um diese zu öffnen */
	if (argc > 1) {
		cout << "Argument gefunden. Versuche, Datei " << argv[1] << " zu öffnen." << endl;
		try {
			personen = createListFromFile(argv[1]);
		}
		catch (runtime_error e) {
			cout << e.what() << endl;
		}
	}

}

list<Person> createListFromFile(string filename) {
	ifstream readFile;
	
	/* fstream benötigt ein c-style char Array als Variable für den Dateinamen */
	readFile.open(filename.c_str());

	if (!readFile.is_open()) {
		throw runtime_error("Error: Datei '" + filename + "' konnte nicht geöffnet werden.\n\tExistiert die Datei und besitzen Sie die nötigen Rechte?");
	}

	/* Die Datei kann an diesem Punkt gelesen werden */
	string line;
	/* Erste Zeile mit den Namen der Werte lesen und diese speichern */
	getline(readFile, line);
	if (line.empty()) {
		throw runtime_error("Error: Datei '" + filename + "' enthält keine Daten.");
	}
	vector<string> identifiers;

	while ( getline(readFile, line) ) {
		
	}	
	
	readFile.close();
	
	list<Person> personen;
	return personen;

}

/* Findet die Stellen, an denen ein Komma steht, sodass die Zeile dort in die einzelnen Werte aufgeteilt werden kann */
vector<string> readValuesFromLine(string line) {
	vector<string> values;	
	int commaPosition = 0, valueStartPosition = 0;
	
	while ( (commaPosition = line.find(",", commaPosition)) != -1 ) {
		cout << "Komma bei " << commaPosition << endl;
		/* Extrahiert die Werte und speichert sie */
		values.push_back(line.substr(valueStartPosition, commaPosition - valueStartPosition));	
	
		/* Der Anfang des nächsten Wertes muss festgehalten werden */
		valueStartPosition = commaPosition + 1;

		commaPosition++;
	}
	for (vector<string>::iterator i = values.begin(); i < values.end(); i++) {
		cout << *i << ",";
	}
	return 	values;
}
