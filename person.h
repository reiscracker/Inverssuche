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
		string _name, _vorname;
		string _telefonPrivat, _telefonDienstlich;
		string _handyPrivat, _handyDienstlich;
		string _faxPrivat, _faxDienstlich;

	public:
		Person(const string *personenDaten);
		Person(int id, string name, string vorname, string telefonPrivat,
			string telefonDienstlich, string handyPrivat, string handyDienstlich,
			string faxPrivat, string faxDienstlich);

		string ausgabe() const;
};

