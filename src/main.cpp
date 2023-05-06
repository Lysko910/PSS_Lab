
#include <iostream>
#include "helper.cpp"
#include "../include/ARX.h"
#include "../include/PI.h"
#include "../include/PD.h"
#include "../include/PID.h"
using std::cout;
using std::cin;
using std::endl;

int main()
{	
	// stworzenie obiektu 
	ARX arx({ -0.904837418035960}, {0.190325163928081 });
	// wpisanie konfiguracji
	arx.writeConfig();
	// odczyt konfiguracji
	arx.readConfig();
	//wpisanie odczytanej konfiguracji
	cout<<arx<<endl;

	//symulacja odpowiedzi na skok jednostkowy
	constexpr size_t LICZ_ITER = 50;
    std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu, 
    std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

    // Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
    for (int i = 0; i < LICZ_ITER; i++)
        sygWe[i] = !!i;

	std::cout<< "ARX"<<std::endl;
    // Symulacja modelu na skok 
    for (int i = 0; i < LICZ_ITER; i++){
        faktSygWy[i] = arx.symuluj(sygWe[i]);
		std::cout<< faktSygWy[i] <<std::endl;
	}
	// regulacja PI
	PI pid(2.5);
    std::vector<double> Y(LICZ_ITER);  // faktyczna sekwencja wy
 	std::cout<< "ARX + PID"<<std::endl;
	for (int i = 1; i < LICZ_ITER; i++){
		double u = pid.symuluj(Y[i-1]);
		std::cout<< u <<"\t";
        Y[i] = arx.symuluj(u);
		std::cout<< Y[i]<<std::endl;
	}


	plotToFile<double>(faktSygWy,Y);
    return 0;
}
