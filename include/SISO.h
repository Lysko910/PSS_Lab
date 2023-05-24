#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <iterator>
#include <deque>
#include <map>
#include <random>
#include "../src/helper.cpp"
#include "struktury.h"


class Komponent;
 /**
 * @brief Klasa interfejsowa dla obiektow typu SISO (Single Input Single Output)
 */

class SISO: public Komponent{
public:
	 virtual ~SISO();
	
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
	virtual double symuluj(double n_U)=0;
};

