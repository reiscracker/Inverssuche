

#include <stdexcept>

#include "tree.h"

Tree::Tree() {
    _startingNode = new Node('+');
}

Tree::~Tree() {
    delete(_startingNode);
}

void Tree::normalizeNumber(string &number) {
    if (number.at(0) != '+') {
        cout << "Normalizing " << number << " to " << "+"+number << endl;
        number = "+" + number;
    }
}

void Tree::registerNumber(string number, Person* numberOwner) {
    normalizeNumber(number);
    try {
        _startingNode->registerNumber(number, numberOwner);
    }
    catch (runtime_error e) {
        throw e;
    }
   
}
        
Person* Tree::getPerson(string number) {
    normalizeNumber(number);
    try {
        return _startingNode->getPerson(number);
    }
    catch (runtime_error e) {
        throw e;
    }
}