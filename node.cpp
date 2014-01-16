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

Node::Node(char digit) : _digit(digit) {}

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
    cout << "Ziffer an der ersten Stelle ist: " << number.at(0) << endl;
    if ((number.at(0)) != _digit) {
        cerr << "Fehler: erste Ziffer der Nummer (" << number.at(0) <<
                ") entspricht nicht Ziffer dieses Objektes (" << _digit << ")." << endl;
        return;
    }
    
    /* Sind wir an der letzten Ziffer angekommen? */
    if (number.length() == 1) {
        cout << "Angekommen!!" << endl;
        _personWithThisNumber = numberOwner;
    }
    else {

        /* Erste Ziffer der Nummer "abschneiden" */
        number = number.substr(1, number.length());
        cout << "Nummer ist jetzt: " << number << endl;

        /* Nummer an die nächste Ziffer weitergeben */
        getNextDigit(number.at(0))->registerNumber(number, numberOwner);

    }
}

Person* Node::getPerson(string number) {
    /* Prüfen, ob erste Ziffer auch der Ziffer dieses Objektes entspricht */
    cout << "Ziffer an der ersten Stelle ist: " << number.at(0) << endl;
    if ((number.at(0)) != _digit) {
        cerr << "Fehler: erste Ziffer der Nummer (" << number.at(0) <<
                ") entspricht nicht Ziffer dieses Objektes (" << _digit << ")." << endl;
        return NULL;
    }
    
    /* Sind wir an der letzten Ziffer angekommen? */
    if (number.length() == 1) {
        cout << "Angekommen!!" << endl;
        return _personWithThisNumber;
    }
    else {
        /* Wenn nicht, erste Ziffer der Nummer "abschneiden" */
        number = number.substr(1, number.length());
        cout << "Nummer ist jetzt: " << number << endl;

        /* Die nächste Ziffer finden. Existiert keine, wird ein Fehler zurückgegeben */
        for (list<Node*>::iterator i = _nextDigits.begin(); i != _nextDigits.end(); i++ ) {
            if ((*i)->getDigit() == number.at(0)) {
                cout << "Nächste Ziffer gefunden: " << number.at(0) << endl;
                return (*i)->getPerson(number);
            }
        }
        
        return NULL;
    }
}

char Node::getDigit() {
    return _digit;
}