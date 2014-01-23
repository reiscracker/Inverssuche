/* 10.01.2014
 * Author: Christine Hecht <s0539719@htw-berlin.de>
 * Author: Simon Arnold <s0539710@htw-berlin.de>
 *
 * Die Klasse Tree bildet das Gerüst um die einzelnen Knotenpunkte des Baumes und 
 * kann verschiedene Operationen auf den Baum ausführen.
 */

#ifndef TREE_H
#define	TREE_H
using namespace std;

#include <iostream>
#include "node.h"

class Tree {
    private:
        Node* _startingNode;
        
        /* Die Nummer wird "normalisiert", also in das E.164-Format überführt, wobei:
         *  - Mit + beginnende Nummern bereits als im E.164-Format angenommen werden 
         *  - Eine führende 0 durch +49 ersetzt wird
         *  - Nummern mit anderen, führenden Ziffern durch +49 30 ergänzt werden 
         *      @param number Nummer, die normalisiert werden soll 
         *      @exception runtime_error Fehler, falls die Nummer nicht gültig oder zu lang ist */
        void normalizeNumber(string& number);
        
    public:
        Tree();
        ~Tree();
        
        /* Testet, ob ein String eine Nummer ist (keine Zeichen ausser Ziffern)
         *      @param number String, der geprüft wird
         *      @returns wahr, wenn der String eine Nummer ist */
        bool isNumber(const string& number);
        
        /* Gibt die Nummer an den Startknoten weiter, sodass diese im Baum hinzugefügt wird 
         *      @param number Nummer, die in den Baum gespeichert werden soll
         *      @param numberOwner Person, der diese Nummer gehört */
        void registerNumber(string number, Person* numberOwner);
        
        /* Gibt die Nummer an den Startknoten weiter, sodass die Person für die Nummer aus dem
         * Baum geliefert wird 
         *      @param number Nummer, deren zugehörige Person gesucht werden soll
         *      @returns Person-Objekt, wenn gefunden */
        Person* getPerson(string number);

        /* Holt die Informationen für einen in der DOT-Sprache formulierten Graphen aus dem Baum
         * und schreibt diese in eine Text-Datei. Die Text-Datei wird in ein Bild umgewandelt und 
         * angezeigt. */
        void makeGraph();
};

#endif	/* TREE_H */

