/* 08.01.2014
 * Author: Christine Hecht <s	@htw-berlin.de>
 * Author: Simon Arnold <s0539710@htw-berlin.de>
 *
 * Objekte der Klasse Person enthalten genau eine Person mit ihren Telefonnummern.
 * Diese Objekte werden im Hauptprogramm zu einer Liste verknüpft, um die eingelesenen Personen zu speichern.
*/
using namespace std;
#include <string>

class Person {

	private:
		int _id;
		string name, vorname;
		string telefonPrivat, telefonDienstlich;
		string handyPrivat, handyDienstlich;
		string faxPrivat, faxDienstlich;

	public:
		Person(const string const *personenDaten);
		string ausgabe() const;
}

