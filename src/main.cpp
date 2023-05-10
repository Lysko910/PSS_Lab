
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

 /**
  * \class Generator (component)
  * @brief Klasa interface dla genertorow i ich dekoratorow
  */
class Generator{
public:
virtual ~Generator(){};
virtual double generuj() = 0;

};

/**
  * \class Generator (concrete_component)
  * @brief Klasa interface dla genertorow i ich dekoratorow
  */
class GeneratorConst: public Generator{
private:
double m_val;
public:
GeneratorConst(double n_val = 0.0):m_val(n_val){};
double generuj()override{
	return this->m_val;
}

};

/**
  * \class Decorator (interface do dekoratorw)
  * @brief Klasa interface dla dekoratorow
  * */
class Decorator :public Generator{
protected:
  Generator* m_generator;
  unsigned int m_licznik_wywolan = 0;
public:
  Decorator(Generator* n_generator): m_generator(n_generator){
  };

  double generuj()override{
	return this->m_generator->generuj();
}
	
};

/**
  * \class Decorator  prostokata(interface do dekoratorw)
  * @brief Klasa implementujaca konkretny dekorator typu prostokat
  * */
class DecoratorProstokat:public Decorator{
private:
unsigned int m_T;
public:
DecoratorProstokat(Generator* n_generator,unsigned int n_T):Decorator(n_generator),m_T(n_T){  
}

double generuj()override{
	double val = Decorator::generuj();
  double half_T = m_T/2.0;
  if(m_licznik_wywolan >m_T){
    m_licznik_wywolan= 0;
  }else{
    m_licznik_wywolan++;
  }
      if(m_licznik_wywolan <=half_T){
        return val;
      }else if(m_licznik_wywolan>half_T){
        return 0.0;
      }
}

};




int main()
{	
  Generator* g =new GeneratorConst(1.0);
  Generator* d1 = new DecoratorProstokat(g,10);
	for(int i=0;i<100;i++){
  double val = d1->generuj();
	std::cout<<val<<std::endl;	
	}


	//plotToFile<double>(signal);
    return 0;
}
