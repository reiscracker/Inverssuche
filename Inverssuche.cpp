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
#include "tree.h"

#define FIRSTNUMBERATTRIBUTE 3
#define LASTNUMBERATTRIBUTE 8

list<Person*> createListFromFile(string filename);
vector<string> readValuesFromLine(string line);
void userMenu();

Tree* const tree = new Tree();

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
                // An diesem Punkt wurden noch keine Objekte der Liste hinzugefügt, also ist kein delete notwendig 
                return 0;
            }
        }
		
        userMenu();

        delete(tree);
        
        /* Hier besteht die Liste und ist mit Person-Objekten gefüllt */
        for (list<Person*>::iterator i = personen.begin(); i != personen.end(); i++) {
                delete(*i);
                *i = NULL;
        }
}

/* Erstellt eine Liste von Person-Objekten aus einer .csv Datei */
list<Person*> createListFromFile(string filename) {
	list<Person*> personen;
	ifstream readFile;
	
	/* fstream benötigt ein c-style char Array als Variable für den Dateinamen */
	readFile.open(filename.c_str());

	if (!readFile.is_open()) {
		throw runtime_error("Error: Datei '" + filename + "' konnte nicht geöffnet werden.\n\tExistiert die Datei und besitzen Sie die nötigen Rechte?");
	}

	/* Die Datei kann an diesem Punkt gelesen werden
	 * Erste Zeile mit den Namen der Werte lesen und diese speichern */
	string line;
	getline(readFile, line);
	if (line.empty()) {
		throw runtime_error("Error: Datei '" + filename + "' enthält keine Keys in der ersten Zeile.");
	}
	vector<string> keys = readValuesFromLine(line);

	/* Jede Zeile wird gelesen, von readValuesFromFile in ihre einzelnen Werte zerlegt und anschließend als Paare in ein
        *  Objekt der Klasse Person gespeichert */
	while ( getline(readFile, line) ) {
            Person* newPerson = new Person;
            personen.push_back(newPerson); 	

            vector<string> values = readValuesFromLine(line);	

            /* Paare mit den zugehörigen Keys und Werten werden angelegt */
            vector<string>::iterator keysIterator = keys.begin();
            vector<string>::iterator valuesIterator = values.begin();
            
            while (keysIterator < keys.end() && valuesIterator < values.end()) {
                
                // Sollte eine Nummer nicht gültig sein, so wird diese auch nicht zu einer Person hinzugefügt 
                if (valuesIterator >= values.begin() + FIRSTNUMBERATTRIBUTE && valuesIterator <= values.begin() + LASTNUMBERATTRIBUTE) {
                    if (!tree->isNumber(*valuesIterator)) {
                        keysIterator++;
                        valuesIterator++;
                        continue;
                    }
                }
                
                // Datenpaar zum aktuellen Personenobjekt hinzufügen
                personen.back()->addValue(*keysIterator, *valuesIterator);

               /* Jede Nummer wird mit dem aktuellen Personen-Objekt verknüpft.
                * Eigentlich ist dieses Programm flexibel, was die Werte in der .csv Datei anbelangt.
                * Um die Telefonnummern zu identifizieren, muss allerdings angenommen werden, dass 
                * die Werte zwischen FIRSTNUMBERATTRIBUTE und LASTNUMBERATTRIBUTE der .csv Datei Telefonnummern sind */
               if (valuesIterator >= values.begin() + FIRSTNUMBERATTRIBUTE && valuesIterator <= values.begin() + LASTNUMBERATTRIBUTE) {
                   tree->registerNumber(*valuesIterator, personen.back());
               }
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
	values.push_back(line.substr(valueStartPosition, line.size() - valueStartPosition));
	return 	values;
}

void userMenu() {
    bool running = true;
    string menuChoice = "";
    
    while (running) {
        cout << "\nHauptmenü\nSie können:\n * Eine Nummer eingeben, um die zugehörige Person zu finden" <<
                                        "\n * 'g' eingeben, um den Graphen anzuzeigen" <<
                                        "\n * Nichts eingeben und bestätigen, um das Programm zu beenden" << 
                                        "\n > ";
        getline(cin, menuChoice);

        if (menuChoice == "g") {
            tree->makeGraph();
        }
        else if (menuChoice == "") {
            running = false;
        }
        else {
            try {
                    tree->getPerson(menuChoice)->printValues();
            }
            catch (runtime_error e) {
                cerr << e.what() << endl;
            }
        }
    }
}