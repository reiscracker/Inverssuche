

#include <stdexcept>
#include <fstream>
#include <stdlib.h>
#include "tree.h"

Tree::Tree() {
    _startingNode = new Node('+');
}

Tree::~Tree() {
    delete(_startingNode);
}

bool Tree::isNumber(const string& number) {
    /* Eine Telefonnummer muss mindestens zwei Ziffern beinhalten und darf keine Zeichen, ausser einem
     * '+' am Anfang und Ziffern beinhalten */
    if (number.length() <= 1) {
//        throw runtime_error("Fehler: Telefonnummer muss mindestens zwei Ziffern enthalten.");
        return false;
    }
    // Erstes Zeichen prüfen
    if ( !isdigit(number.at(0)) && number.at(0) != '+' ) {
//        throw runtime_error("Fehler: Ungültiges Zeichen in der Telefonnummer.");
        return false;
    }
    // Restliche Zeichen prüfen
    for (int i = 1; i < number.length(); i++) {
        if (!isdigit(number.at(i))) {
//            throw runtime_error("Fehler: Ungültiges Zeichen in der Telefonnummer.");
            return false;
        }
    }
    
    return true;
}

/* Die Nummer wird "normalisiert", also in das E.164-Format überführt, wobei:
     *  - Mit + beginnende Nummern bereits als im E.164-Format angenommen werden 
     *  - Eine führende 0 durch +49 ersetzt wird
     *  - Nummern mit anderen, führenden Ziffern durch +49 30 ergänzt werden */
void Tree::normalizeNumber(string &number) {
    
    if (!isNumber(number)) {
        throw runtime_error("Fehler: Nummer ist nicht gültig.");
    }
    if (number.at(0) == '0') {
        cout << "Normalizing " << number << " to ";
        number.replace(0, 1, "+49");
        cout << number << endl;
    }
    else if (isdigit(number.at(0))) {
        cout << "Normalizing " << number << " to ";
        number.insert(0, "+4930");
        cout << number << endl;
    }
    
    /* Sollte die Nummer nun mehr als 15 Zeichen beinhalten, wird sie abgewiesen */
    if (number.length() > 15) {
        throw runtime_error("Fehler: Nummer enthält im E.164-Format mehr als 15 Zeichen");
    }
}

void Tree::registerNumber(string number, Person* numberOwner) {
    try {
        normalizeNumber(number);
        _startingNode->registerNumber(number, numberOwner);
    }
    catch (runtime_error e) {           
        cout << e.what() << ". Überspringe " << number << endl;
    }
   
}
        
Person* Tree::getPerson(string number) {
    try {
        normalizeNumber(number);
        return _startingNode->getPerson(number);
    }
    catch (runtime_error e) {           // Try-catch Block könnte hier weggelassen werden
        throw e;
    }
}

void Tree::makeGraph() {
    stringstream nodes, labels;
    string numberProgress;
    
    // In DOT lässt sich ein + nicht als Zeichen verwenden, also ändern wir + zu p
    _startingNode->setDigit('p');
    
    // Jeder Knoten schreibt seine Daten in die Stringstreams nodes und labels
    _startingNode->addToGraphString(nodes, numberProgress, labels);
    
    _startingNode->setDigit('+');
    
    /* Die erstellten strings mit der dot-Sprache müssen in eine Datei geschrieben werden */
    ofstream myStream;
    try {
        myStream.open("graph.tmp");
        myStream << "digraph G {\n" << nodes.str() << "\n" << labels.str() << "\n}";
    } catch(exception e) {
        cerr << e.what();
    }
    myStream.close();
    system("dot -Tpng graph.tmp -o graph.png");
    system("rm graph.tmp");
    system("eog graph.png");
    
}