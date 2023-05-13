
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
  Generator* g =new GeneratorConst(2.0);
  //Generator* d1 = new DecoratorSinus(g,5,0.5);
	Generator* d2 = new DecoratorProstokat(g,0);
  //Generator* d3 = new DecoratorSzum(d2,0.2);
  //Generator* d4 = new DecoratorDelay(d3,3);
  //Generator* d5 = new DecoratorNasycenie(d4,1.3);

  for(int i=0;i<100;i++){
  double val = d2->generuj();
	std::cout<<val<<std::endl;	
	}
	//plotToFile<double>(signal);
    return 0;
}
