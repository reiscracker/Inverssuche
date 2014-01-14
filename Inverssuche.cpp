/* 08.01.2014
 * Author: Christine Hecht <s0539719@htw-berlin.de>
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

list<Person*> createListFromFile(string filename);
vector<string> readValuesFromLine(string line);

int main(int argc, const char* argv[]) {
	cout << "Programm gestartet" << endl;
	
	/* Liste in der die Personen aus der Datei gespeichert werden */
	list<Person*> personen;

	/* Es muss mindestens eine Datei angegeben sein um diese zu öffnen */
	if (argc > 1) {
		cout << "Argument gefunden. Versuche, Datei " << argv[1] << " zu öffnen." << endl;
		try {
			personen = createListFromFile(argv[1]);
		}
		catch (runtime_error e) {
			cout << e.what() << endl;
			// An diesem Punkt wurden noch keine Objekte der Liste hinzugefügt, also ist kein free notwendig 
			return 0;
		}
		
		/* Hier besteht die Liste und ist mit Person-Objekten gefüllt */
		for (list<Person*>::iterator i = personen.begin(); i != personen.end(); i++) {
			free(*i);
			*i = NULL;
		}
	}

}

list<Person*> createListFromFile(string filename) {
	list<Person*> personen;
	ifstream readFile;
	
	/* fstream benötigt ein c-style char Array als Variable für den Dateinamen */
	readFile.open(filename.c_str());

	if (!readFile.is_open()) {
		throw runtime_error("Error: Datei '" + filename + "' konnte nicht geöffnet werden.\n\tExistiert die Datei und besitzen Sie die nötigen Rechte?");
	}

	/* Die Datei kann an diesem Punkt gelesen werden */
	/* Erste Zeile mit den Namen der Werte lesen und diese speichern */
	string line;
	getline(readFile, line);
	if (line.empty()) {
		throw runtime_error("Error: Datei '" + filename + "' enthält keine Keys in der ersten Zeile.");
	}
	vector<string> keys = readValuesFromLine(line);

	/* Jede Zeile wird gelesen, von readValuesFromFile in ihre einzelnen Werte zerlegt und anschließend als Paare in ein
 * 		Objekt der Klasse Person gespeichert */
	while ( getline(readFile, line) ) {
		personen.push_back(new Person); 	

		vector<string> values = readValuesFromLine(line);	
		
		/* Paare mit den zugehörigen Keys und Werten werden angelegt */
		vector<string>::iterator keysIterator = keys.begin();
		vector<string>::iterator valuesIterator = values.begin();
		while (keysIterator < keys.end() && valuesIterator < values.end()) {
			/* Speichern der Werte in das Person-Objekt */
			personen.back()->addValue(*keysIterator, *valuesIterator);
			keysIterator++;
			valuesIterator++;
		}
	}	
	
	readFile.close();
	
	return personen;

}

/* Findet die Stellen, an denen ein Komma steht, sodass die Zeile dort in die einzelnen Werte aufgeteilt werden kann */
vector<string> readValuesFromLine(string line) {
	vector<string> values;	
	int commaPosition = 0, valueStartPosition = 0;
	
	while ( (commaPosition = line.find(",", commaPosition)) != -1 ) {
		/* Extrahiert die Werte und speichert sie */
		values.push_back(line.substr(valueStartPosition, commaPosition - valueStartPosition));	
	
		/* Der Anfang des nächsten Wertes muss festgehalten werden */
		valueStartPosition = commaPosition + 1;

		commaPosition++;
	}
	/* Letzter Wert, der aufgrund des fehlenden Kommas nicht gefunden wird, wird hinzugefügt */
	values.push_back(line.substr(valueStartPosition, line.size() - valueStartPosition - 1));
	return 	values;
}
