
#include <iostream>
#include "helper.cpp"
#include "../include/ARX.h"

using std::cout;
using std::cin;
using std::endl;

int main()
{	
	// stworzenie obiektu 
	ARX arx({ -9.2 }, { 0.9}, 2, 0.0);
	// wpisanie konfiguracji
	arx.writeConfig();
	// odczyt konfiguracji
	arx.readConfig();
	//wpisanie odczytanej konfiguracji
	cout<<arx<<endl;

	//zmiana parametrow modelu
	arx.set_A({1.2, 4.1});
	arx.set_B({5.2, 2.0});
	arx.set_k(2);
	arx.set_var(4.0);
	
	// wpisanie konfiguracji
	arx.writeConfig();
	// odczyt konfiguracji
	arx.readConfig();
	//wpisanie odczytanej konfiguracji
	cout<<arx<<endl;

	//symulacja odpowiedzi na skok jednostkowy
	
	constexpr size_t LICZ_ITER = 30;
    std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu, 
    std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

    // Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
    for (int i = 0; i < LICZ_ITER; i++)
        sygWe[i] = !!i;

    // Symulacja modelu:
    for (int i = 0; i < LICZ_ITER; i++){
        faktSygWy[i] = arx.symuluj(sygWe[i]);
		std::cout<< faktSygWy[i] <<std::endl;
	}

    return 0;
}
