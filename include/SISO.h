#pragma once
#include <string>
 /**
 * @brief Klasa interfejsowa dla obiektow typu SISO (Single Input Single Output)
 */

class SISO
{
public:

	SISO(){};
	virtual ~SISO(){};
	 /**
     * @brief Funkcja do jednokrokowej symulacji odpowiedzi obiektu dyksretnego
	 * @param  n_U Wartosc wejsciowa na obiekt dyskretny
     * @return Odpowiedz obiektu dyskretnego
     */
	virtual double symuluj(double n_U) = 0;
	 /**
     * @brief Funkcja zapisujaca konfuguracje do pliku config.ini
	 * @param  nazwa_config Nazwa pod jak konfiguracja ma zostac zapisana do pliku
     */
	virtual void writeConfig(std::string nazwa_config = "") = 0;
	 /**
     * @brief Funkcja odczytujaca konfuguracje z pliku config.ini
	 * @param  nazwa_config Nazwa konfiguracji, do odczytu
     */
	virtual void readConfig(std::string nazwa_config = "") = 0;
};

