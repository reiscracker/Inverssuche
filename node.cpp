/* 10.01.2014
 * Author: Christine Hecht <s0539719@htw-berlin.de>
 * Author: Simon Arnold <s0539710@htw-berlin.de>
 *
 * Objekte der Klasse Person enthalten genau eine Person mit ihren Telefonnummern.
 * Diese Objekte werden im Hauptprogramm zu einer Liste verknüpft, um die eingelesenen Personen zu speichern.
*/
#include "node.h"
#include <iostream>
#include <stdlib.h>
#include <stdexcept>

Node::Node(char digit) : _digit(digit), _personWithThisNumber(NULL) {}

Node::~Node() {
    _personWithThisNumber = NULL;
    
    /* Alle angrenzenden Ziffern löschen */
    list<Node*>::iterator i = _nextDigits.begin();
    while (i != _nextDigits.end()) {
        
        cout << "I am a " << _digit << ". Deleting digit " << (*i)->getDigit() << endl;
        /* Der Iterator ist ein Zeiger auf eine Liste von Zeigern, also muss das dereferenzierte Objekt gelöscht werden*/
        delete(*i);
        i++;
    }
}

Node* Node::getNextDigit(char digit) {
    /* Sollte die Ziffer bereits in der Liste der angrenzenden Ziffern vorhanden sein, wird
        keine neue hinzugefügt */
    for (list<Node*>::iterator i = _nextDigits.begin(); i != _nextDigits.end(); i++ ) {
        if ((*i)->getDigit() == digit) {
            cout << "Digit " << digit << " already exists, won't create it!" << endl;
            return *i;
        }
    }
    
    cout << "Creating new digit: " << digit << endl;
    /* Neue Ziffer anlegen und zurückgeben */
    Node* newNode = new Node(digit);
    _nextDigits.push_back(newNode);
    return newNode;
}

void Node::registerNumber(string number, Person* numberOwner) {
    /* Prüfen, ob erste Ziffer auch der Ziffer dieses Objektes entspricht */
    if ((number.at(0)) != _digit) {
        throw runtime_error( string("Erste Ziffer der Nummer (") + number.at(0) + ") " +
                "entspricht nicht Ziffer dieses Objektes (" + _digit + ") !");
    }
    
    /* Sind wir an der letzten Ziffer angekommen? */
    if (number.length() == 1) {
        _personWithThisNumber = numberOwner;
    }
    else {

        /* Erste Ziffer der Nummer "abschneiden" */
        number = number.substr(1, number.length());

        /* Nummer an die nächste Ziffer weitergeben */
        getNextDigit(number.at(0))->registerNumber(number, numberOwner);
    }
}

Person* Node::getPerson(string number) {
    /* Prüfen, ob erste Ziffer auch der Ziffer dieses Objektes entspricht */
    cout << "Ziffer an der ersten Stelle ist: " << number.at(0) << endl;
    if ((number.at(0)) != _digit) {
        throw runtime_error( string("Erste Ziffer der Nummer (") + number.at(0) + ") " +
                "entspricht nicht Ziffer dieses Objektes (" + _digit + ") !");
    }
    
    /* Sind wir an der letzten Ziffer angekommen? */
    if (number.length() == 1) {
        cout << "Angekommen!!" << endl;
        if (_personWithThisNumber == NULL) {
            throw runtime_error("Keine passende Person gefunden!\n");
        }
        else {
                return _personWithThisNumber;
        }
    }
    else {
        /* Wenn nicht, erste Ziffer der Nummer "abschneiden" */
        number = number.substr(1, number.length());

        /* Die nächste Ziffer finden. Existiert keine, wird ein Fehler zurückgegeben */
        for (list<Node*>::iterator i = _nextDigits.begin(); i != _nextDigits.end(); i++ ) {
            if ((*i)->getDigit() == number.at(0)) {
                return (*i)->getPerson(number);
            }
        }
        
        throw runtime_error( string("Die Rufnummer existiert nicht.\n"));
    }
}

char Node::getDigit() {
    return _digit;
}

void Node::addToGraphString(stringstream& nodes, string numberProgress, stringstream& labelString) {
    
    
    /* Verknüpfung des vorherigen zu diesem Objekt herstellen */
    if (numberProgress != "") {
        nodes << "\"" << numberProgress << "\"" << string("->") << "\"" << numberProgress << _digit << "\""<< string(";\n");
    }
    numberProgress += _digit;
    
    /* Label string ändern. Hier werden die label der einzelnen Knoten beschrieben */
    labelString << "\"" << numberProgress << "\"" << string(" [label=\"") << _digit << string("\"];\n");
    
    /* Sollte eine Rufnummer hier enden, so wird die Person als eigener Knoten angefügt und mit einem Label versehen*/
    if (_personWithThisNumber != NULL) {
        /* Knoten mit namen: VornameName hinzufügen */
        nodes << "\"" << numberProgress << "\"" << string("->") << "\"" << _personWithThisNumber->getValues()->at("Vorname") << _personWithThisNumber->getValues()->at("Name") << "\"" << string(";\n");
        
        /* Label erstellen für den knoten VornameName */
        labelString << "\"" << _personWithThisNumber->getValues()->at("Vorname") << _personWithThisNumber->getValues()->at("Name") << "\"";
        labelString << string(" [label=\"");
        
        /* Alle Werte der anhängenden Person in das Label schreiben*/
        for (map<string, string>::iterator i = _personWithThisNumber->getValues()->begin(); i != _personWithThisNumber->getValues()->end(); i++) {
            labelString << i->first << ": " << i->second << "\\n";
        }
        labelString << string("\"];\n");
    }
    
    for (list<Node*>::iterator i = _nextDigits.begin(); i != _nextDigits.end(); i++ ) {
        (*i)->addToGraphString(nodes, numberProgress, labelString);
    }
    
}

void Node::setDigit(char newDigit) {
        _digit = newDigit;
}