/* 08.01.2014
 * Author: Christine Hecht <s0539719@htw-berlin.de>
 * Author: Simon Arnold <s0539710@htw-berlin.de>
 *
 * Dieses Programm realisiert eine Inverssuche durch einen Baum von Telefonnummern. Eine Liste von Nummern wird
 * aus einer Datei eingelesen, die Nummern werden anschließend in einen Baum gespeichert, wobei jeder Knoten
 * des Baumes eine Ziffer in der Telefonnummer darstellt. Es ist dann möglich, anhand einer 
 * Telefonnummer den Namen und weitere Telefonnummern des Besitzers der Nummer herauszufinden.
 * Weiterhin erlaubt dieses Programm es, den erstellten Baum als Graphen darzustellen. 
 * */
using namespace std;
#include <list>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "tree.h"

#define FIRSTNUMBERATTRIBUTE 3  // Der Wert, der in einer Zeile der .csv Datei die erste Telefonnummer enthält
#define LASTNUMBERATTRIBUTE 8 // Der Wert, der in einer Zeile der .csv Datei die letzte Telefonnummer enthält

list<Person*> createListFromFile(string filename);
vector<string> readValuesFromLine(string line);
void userMenu();

/* Globales Objekt der Klasse Tree, die Operationen auf den Baum realisiert */
Tree* const tree = new Tree();

int main(int argc, const char* argv[]) {
    
	/* Liste erstellen, in der die aus der .csv Datei gelesenen Personen gespeichert werden */
	list<Person*> personen;

	/* Das Programm muss mit einer Datei als Parameter aufgerufen werden*/
	if (argc == 2) {
            cout << "Argument gefunden. Lese Datei " << argv[1] << "." << endl;
            
            try {
                /* Liest die Personen aus der .csv Datei und erstellt außerdem den Baum */
                personen = createListFromFile(argv[1]);
            }
            catch (runtime_error e) {
                cout << e.what() << endl;
                /* Schlägt das Lesen der Datei fehl, wird das Programm beendet*/
                return 0;
            }
        }
		
        userMenu();

        /* Der Baum räumt sich selbst auf */
        delete(tree);
        
        /* Hier besteht die Liste und ist mit Person-Objekten gefüllt */
        for (list<Person*>::iterator i = personen.begin(); i != personen.end(); i++) {
                delete(*i);
                *i = NULL;
        }
}

/* Erstellt eine Liste von Person-Objekten aus einer .csv Datei und fügt jede gelesene Telefonnummer
 * dem Baum der Telefonnummern hinzu.
 *      @param filename Pfad der zu öffnenden .csv-Datei
 *      @returns Erstellte Liste von Personen-Objekten */
list<Person*> createListFromFile(string filename) {
	
        list<Person*> personen;
	ifstream readFile;
	
	readFile.open(filename.c_str());
	if (!readFile.is_open()) {
		throw runtime_error("Error: Datei '" + filename + "' konnte nicht geöffnet werden.\n\tExistiert die Datei und besitzen Sie die nötigen Rechte?");
	}

	/* Die Datei kann an diesem Punkt gelesen werden
	 * Erste Zeile mit den Attributsbezeichnern der Werte lesen und diese speichern */
	string line;
	getline(readFile, line);
	if (line.empty()) {
		throw runtime_error("Error: Datei '" + filename + "' enthält keine Werte in der ersten Zeile.");
	}
	vector<string> keys = readValuesFromLine(line);

	/* Jede Zeile wird gelesen, von readValuesFromFile in ihre einzelnen Werte zerlegt und 
         * in ein Objekt der Klasse Person gespeichert */
	while ( getline(readFile, line) ) {
            
            Person* newPerson = new Person;
            personen.push_back(newPerson); 	

            vector<string> values = readValuesFromLine(line);	

            /* Werte in die gerade angelegte Person schreiben */
            vector<string>::iterator keysIterator = keys.begin();
            vector<string>::iterator valuesIterator = values.begin();
            while (keysIterator < keys.end() && valuesIterator < values.end()) {
                
                /* Wenn der Wert als Nummer angesehen werden soll (zwischen FIRSTNUMBERATTRIBUTE und LASTNUMBERATTRIBUTE),
                 * wird die Nummer auf Gültigkeit geprüft */
                if (valuesIterator >= values.begin() + FIRSTNUMBERATTRIBUTE && 
                    valuesIterator <= values.begin() + LASTNUMBERATTRIBUTE) {
                    
                    if (!tree->isNumber(*valuesIterator)) {
                        /* Ungültige Nummer gefunden, springe weiter zum nächsten Wert */
                        keysIterator++;
                        valuesIterator++;
                        continue;
                    }
                }
                
                /* Attributsname - Wert Paar zum Objekt hinzufügen */
                personen.back()->addValue(*keysIterator, *valuesIterator);

               /* Wenn der gerade gelesene Wert als Nummer angesehen werden soll, wird er
                * außerdem zum Baum hinzugefügt */
               if (valuesIterator >= values.begin() + FIRSTNUMBERATTRIBUTE && valuesIterator <= values.begin() + LASTNUMBERATTRIBUTE) {
                   tree->registerNumber(*valuesIterator, personen.back());
               }
                
               keysIterator++;
               valuesIterator++;
            } // while (keysIterator < keys.end() && valuesIterator < values.end())
            
	} // while getline
	readFile.close();
	return personen;
}

/* Findet die Positionen der Kommata in einer Zeile und extrahiert die Werte zwischen diesen.
 *      @param line Zeile, aus der die Werte extrahiert werden sollen
 *      @returns vector<String> mit den extrahierten Werten */
vector<string> readValuesFromLine(string line) {
    
	vector<string> values;	
	int commaPosition = 0, valueStartPosition = 0;
	
        /* Solange noch ein weiteres Komma gefunden werden kann */
	while ( (commaPosition = line.find(",", commaPosition)) != -1 ) {
		
                /* Wert zwischen letztem und aktuell gefundenen Komma extrahieren */
                values.push_back(line.substr(valueStartPosition, commaPosition - valueStartPosition));	
	
		/* Position des aktuell gefundenen Kommas festhalten */
		valueStartPosition = commaPosition + 1;
		commaPosition++;
	}
        
	/* Letzten Wert, der aufgrund des fehlenden Kommas nicht gefunden wird, hinzufügen */
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