/* 10.01.2014
 * Author: Christine Hecht <s0539719@htw-berlin.de>
 * Author: Simon Arnold <s0539710@htw-berlin.de>
 *
 * Objekte der Klasse Person enthalten genau eine Person mit ihren Telefonnummern.
 * Diese Objekte werden im Hauptprogramm zu einer Liste verknüpft, um die eingelesenen Personen zu speichern.
*/
#include "node.h"


Node::Node(int digit) : _digit(digit) {
    _nextDigits
}

Node::~Node() {
    /* Wird in Inverssuche.cpp "befreit" */
    _personWithThisNumber = NULL;
    
    /* Alle angrenzenden Ziffern löschen */
    for (list<Node>::iterator i = _nextDigits.begin(); i != _nextDigits.end(); i++) {
        delete(i);
    }
    cout << "Node " + _digit + " deleted" << endl;
}
Node* Node::createNextDigit(int digit) {
    Node* newNode = new Node(digit);
    _nextDigits.push_back(newNode);
    return newNode;
}

Person* Node::addNumber(string number, Person* numberOwner) {
		
}

void Node::getPerson(string number) {
    
}

int Node::getDigit() {
    return _digit;
}