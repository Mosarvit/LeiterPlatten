#include <iostream>

#include "GUI.h"
#include "PreisAngebot.h"


//---------------------------------------------------------------------------------------------------------------------

// returns the choosen Menu-Point
//int GUI::showMenu()
//{
//	std::cout << "Bitte waehlen Sie eine Option:" << std::endl
//		<< "1 - Neuer Auftrag" << std::endl
//		<< "2 - Ausgabe aller Firmen mit Umsaetzen " << std::endl
//		<< "3 - Beenden" << std::endl;
//		 
//	return inputNumber("Ihre Eingabe: ");
//}

int GUI::showMenu()
{
	std::cout << "Bitte wählen Sie eine Zahl für die jeweilige Aktion:" << std::endl
		<< "1 - Neue Buchung" << std::endl
		<< "2 - Ausgabe aller Buchungen" << std::endl
		<< "3 - Beenden" << std::endl;

	std::cout << "Eingabe: ";
	int eingabe;
	std::cin >> eingabe;
	return eingabe;
}

//---------------------------------------------------------------------------------------------------------------------

// gibt true zurück, wenn die vom Nutzer gewählte Route gebucht werden soll.
bool GUI::angebotBerechnung(Node& rStart, Node& rEnde)
{
	PreisMap *currentPreisMap;
	int anzahl = 0;
	string word;
	deque<Edge*> result;

	
	
	anzahl = inputNumber("Bitte geben Sie die Anzahl an: ");
	
	if (anzahl >= 1000) {

		currentPreisMap = *(next(m_rPreisMaps.begin(), 2));

	}else if (anzahl >= 100) {

		currentPreisMap = *(next(m_rPreisMaps.begin(), 1));

	}else {

		currentPreisMap = *(next(m_rPreisMaps.begin(), 0));
	}

	currentPreisMap->findShortestPathDijkstra(result, &rStart, &rEnde);

	for (auto edge : result) {

		cout << edge->toString() << endl;
	}

	//if (path.empty()) {
	//	throw TravelGuiException("Für die gewählten Orte wurde keine Route gefunden.");
	//}

	//double price = 0.0;
	//int minutes = 0;

	//// Gefundene Strecke durchlaufen
	//for (std::deque<Edge*>::iterator it = path.begin(); it != path.end(); it++)
	//{
	//	// ist es eine Flugverbindung? (dynamic_cast gibt NULL zurück, wenn der Cast von der Basisklasse zur abgeleiteten Klasse ungültig ist!)
	//	if (FlightRoute* pFlight = dynamic_cast<FlightRoute*>(*it)) {
	//		std::cout << "Flug: " << pFlight->toString() << "; Dauer: " << pFlight->getMinutes() << "min" << std::endl;
	//		price += pFlight->getPrice();       // Preis für den Streckenabschnitt addieren
	//		minutes += pFlight->getMinutes();   // Zeit für den Streckenabschnitt addieren
	//	}
	//	// ist es eine Busverbindung?
	//	else if (BusRoute* pBus = dynamic_cast<BusRoute*>(*it)) {
	//		std::cout << "Bus: " << pBus->toString() << "; Dauer: " << pBus->getMinutes() << "min" << std::endl;
	//		price += pBus->getPrice();
	//		minutes += pBus->getMinutes();
	//	}
	//}

	//std::cout << "Gesamtdauer: " << minutes << ", Preis: " << price << std::endl;

	///*
	//* Soll die Route gebucht werden??
	//*/
	//std::string bBook;
	//std::cout << "Moechten Sie diese Route buchen? [j/n]: ";
	//std::cin >> bBook;
	//// Überspringe das alles, falls die Route nicht gebucht werden soll!
	//if (bBook == "j")
	//{
	//	std::string firstname, lastname;
	//	std::cout << "Bitte Vornamen eingeben: ";
	//	std::cin >> firstname;
	//	std::cout << "Bitte Nachnamen eingeben: ";
	//	std::cin >> lastname;

	//	std::string address1, address2;
	//	std::cout << "Bitte Strase und Hausnummer eingeben: ";
	//	std::cin >> address1;
	//	std::cout << "Bitte PLZ und Ort eingeben: ";
	//	std::cin >> address2;

	//	if (firstname.empty() || lastname.empty() || address1.empty() || address2.empty()) {
	//		throw TravelGuiException("Die Personenangaben sind unvollständig.");
	//	}

	//	Booking b;
	//	b.m_pStart = pSrcCity;
	//	b.m_pDst = pDstCity;
	//	b.m_firstname = firstname;
	//	b.m_lastname = lastname;
	//	b.m_address1 = address1;
	//	b.m_address2 = address2;
	//	b.m_price = price;

	//	// in die Liste der Buchungen einfügen
	//	m_bookings.push_back(b);

	//	return true;
	//}

	return false;
}

//int GUI::inputNumber(string question)
//{
//	return 0;
//}


//---------------------------------------------------------------------------------------------------------------------


/*
* Liest so lange ein, bis eine gültge Stadt eingegeben wurde oder 'q' gedrückt wurde
*/
int GUI::inputNumber(string question)
{
	int n;
	bool fail = true;	

	while (fail)  
	{
		cout << question << endl;
		cin >> n;

		if (!cin){

			cin.clear(); 
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
			cout << "Fehlerhafte Eingabe!" << endl;

		}else{
			fail = false;
		}
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return n;
}

string GUI::inputString(string question)
{
	string input;
	bool fail = true;

	while (fail)  
	{
		cout << question << endl;
		getline(cin, input);

		if (!cin) {

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Fehlerhafte Eingabe!" << endl;
		}
		else {
			fail = false;
		}
	}
	return input;
}


//---------------------------------------------------------------------------------------------------------------------

//void TravelGUI::showBookingList()
//{
//	std::cout << "\n--------------------------------------------------------------" << std::endl;
//
//	for (std::list<Booking>::iterator it = m_bookings.begin(); it != m_bookings.end(); it++)
//	{
//		/*
//		* Hinweis zur Nutzung des Iterators:
//		* ----------------------------------
//		* std::list<Booking> enthält direkt Booking-Objekte, KEINE Pointer! ---> UNTERSCHIED ZUR NODE-LISTE!
//		* Der dereferenzierte Iterator (*it) ist also kein Pointer, sondern ein Booking-Objekt.
//		* (*it).m_pStart ist das Selbe wie it->m_pStart. (Pfeiloperator geht bei Iteratoren genauso wie bei Pointern)
//		* ---> Darum kann hier der Pfeiloperator genutzt werden, um direkt auf die Elemente des Booking-Objektes zuzugreifen.
//		*
//		* Unterschied zur Node-Liste:
//		* Bei einer std::list<Node*> musste der Iterator zuerst dereferenziert werden. (*itNode)
//		* Der Pfeiloperator hat sich dann auf den gespeicherten Pointer bezogen, z.B: (*itNode) -> getId();
//		*/
//
//		if (it->m_pStart != NULL && it->m_pDst != NULL)
//		{
//			std::cout << "Verbindung: " << it->m_pStart->getID() << " -> " << it->m_pDst->getID() << std::endl;
//			std::cout << "Name:       " << it->m_firstname << " " << it->m_lastname << std::endl;
//			std::cout << "Addresse 1: " << it->m_address1 << std::endl;
//			std::cout << "Addresse 2: " << it->m_address1 << std::endl;
//			std::cout << "Gesamtpreis: " << it->m_price;
//
//			std::cout << "\n--------------------------------------------------------------" << std::endl;
//		}
//	}
//}
//
//
////---------------------------------------------------------------------------------------------------------------------
