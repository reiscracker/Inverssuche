#include <stdexcept>
#include <fstream>
#include <stdlib.h>
#include "tree.h"

#define MAXNUMBERLENGTH 15

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
        return false;
    }
    
    /* Erstes Zeichen prüfen */
    if ( !isdigit(number.at(0)) && number.at(0) != '+' ) {
        return false;
    }
    
    /* Restliche Zeichen prüfen */
    for (int i = 1; i < number.length(); i++) {
        if (!isdigit(number.at(i))) {
            return false;
        }
    }
    
    return true;
}


void Tree::normalizeNumber(string &number) {
    
    if (!isNumber(number)) {
        throw runtime_error("Fehler: Nummer ist nicht gültig.");
    }
    
    if (number.at(0) == '0') {
        number.replace(0, 1, "+49");
    }
    
    else if (isdigit(number.at(0))) {
        number.insert(0, "+4930");
    }
    
    /* Sollte die Nummer nun mehr als 15 Zeichen beinhalten, wird sie abgewiesen */
    if (number.length() > MAXNUMBERLENGTH) {
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
    
    /* Jeder Knoten schreibt seine Daten in die Stringstreams nodes und labels */
    _startingNode->addToGraphString(nodes, numberProgress, labels);
    
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