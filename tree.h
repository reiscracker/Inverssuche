/* 10.01.2014
 * Author: Christine Hecht <s0539719@htw-berlin.de>
 * Author: Simon Arnold <s0539710@htw-berlin.de>
 *
 *
 * Die Klasse Tree bildet das Gerüst um die einzelnen Knotenpunkte des Baumes und 
 * kann verschiedene Operationen auf den Baum ausführen
 */

#ifndef TREE_H
#define	TREE_H
using namespace std;

#include <iostream>
#include "node.h"

class Tree {
    private:
        Node* _startingNode;
        void normalizeNumber(string& number);
        
    public:
        Tree();
        ~Tree();
        
        bool isNumber(const string& number);
        void registerNumber(string number, Person* numberOwner);
        Person* getPerson(string number);

        void makeGraph();
};

#endif	/* TREE_H */

