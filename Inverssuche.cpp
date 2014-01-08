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
#include "person.h"

list<Person> readFromFile(string filename);


int main(int argc, const char* argv[]) {
	cout << "Programm gestartet" << endl;
	
	/* Liste in der die Personen aus der Datei gespeichert werden */
	list<Person> personen;

	/* Es muss mindestens eine Datei angegeben sein um diese zu öffnen */
	if (argc > 1) {
		cout << "Argument gefunden. Versuche, Datei " << argv[1] << " zu öffnen." << endl;
		try {
			personen = readFromFile(argv[1]);
		}
		catch (string error) {
			cout << error << endl;
		}
	}

}

list<Person> readFromFile(string filename) {
	ifstream readFile;
	
	/* fstream benötigt ein c-style char Array als Variable für den Dateinamen */
	readFile.open(filename.c_str());

	if (!readFile.is_open()) {
		string errorString = "Konnte Datei nicht öffnen! Existiert die Datei und besitzen Sie ausreichende Rechte?";
		throw errorString;
	}

	/* Die Datei kann an diesem Punkt gelesen werden */
	string line;
	while ( getline(readFile, line) ) {
		cout << line << endl;
	}	
	
	readFile.close();
	
	list<Person> personen;
	return personen;
}
