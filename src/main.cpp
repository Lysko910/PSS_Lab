
#include <iostream>
#include "../include/ARX.h"
#include "../include/PI.h"
#include "../include/PD.h"
#include "../include/PID.h"
#include "../include/generator.h"

using std::cout;
using std::cin;
using std::endl;



int main(void){	
  //twirzenie generatorow
  Generator* generator_const =new GeneratorConst(3.0);
  Generator* generator_skok = new DecoratorDelay(generator_const,10);
  
  //twirzenie obiektow
  Komponent * objekt1 = new PID(1.2, 0.05, 0.01, 1.0);
  Komponent * objekt2 = new ARX({-0.6 }, { 1 }, 0, 0.0);
  Komponent * objekt3 = new ARX({-0.3 }, { 1 }, 0, 0.0);

 
   Komponent * struktura2 = new StrukturaRownolegla();
    struktura2->dodaj(objekt3);
    struktura2->dodaj(objekt2);
 // utworzenie struktury szeregowej z obiektami
  Komponent * struktura1 = new StrukturaSzeregowa();
  struktura1->dodaj(objekt1);
  struktura1->dodaj(struktura2);

  //test struktura szeregowa
  // wartosc zadana

  double w =0.0;
  double y =0.0;
  double e =0.0;
  //  PID->ARX
  for(int i=0;i<300;i++){
    // wartosc zadana
  w = generator_const->generuj();
  // Wezel e = w-y;
  e = w - y;
  y = struktura1->symuluj(e);
	std::cout<<y<<std::endl;	
	}
	
  delete generator_const;
  delete generator_skok;
  delete objekt1;
  delete objekt2;
   delete objekt3;
  delete struktura1;
  delete struktura2;
    return 0;
}
