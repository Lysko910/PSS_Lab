
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
  Generator* generator_const =new GeneratorConst(1.0);

  Generator* generator_skok = new DecoratorDelay(generator_const,10);
  
  Komponent * objekt1 = new ARX({ -0.8, 0.4 }, { 1 }, 1, 0.0);
  Komponent * objekt2 = new ARX({ -0.8, 0.4 }, { 1 }, 1, 0.0);
  //Komponent * struktura1 = new StrukturaRownolegla();
  Komponent * struktura1 = new StrukturaSzeregowa();
  struktura1->dodaj(objekt1);
  struktura1->dodaj(objekt2);
  for(int i=0;i<100;i++){
  double val = generator_skok->generuj();
  val = struktura1->symuluj(val);
	std::cout<<val<<std::endl;	
	}
	
  delete generator_const;
  delete generator_skok;
    return 0;
}
