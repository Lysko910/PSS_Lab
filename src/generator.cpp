 #include "../include/generator.h"

Generator::Generator(){}

Generator::~Generator(){}

GeneratorConst::~GeneratorConst(){}

GeneratorConst::GeneratorConst(double n_val ):m_val(n_val){
}

double GeneratorConst::generuj(){
	return this->m_val;
}

Decorator::Decorator(Generator* n_generator): m_generator(n_generator){
}

Decorator::~Decorator(){}

double Decorator::generuj(){
	return this->m_generator->generuj();
}

DecoratorProstokat::~DecoratorProstokat(){}

DecoratorProstokat::DecoratorProstokat(Generator* n_generator, int n_T,double n_wyp ):Decorator(n_generator),m_T(n_T),m_wyp(n_wyp){  
}

double DecoratorProstokat::generuj(){
double val = Decorator::generuj();
  double half_T = this->m_T*this->m_wyp;
      if(this->m_licznik_wywolan>=half_T){
        val = 0.0;
      }

  if(this->m_licznik_wywolan >=this->m_T-1){
    this->m_licznik_wywolan= 0;
  }else{
    this->m_licznik_wywolan++;
  }
  return val;
}


DecoratorSinus::DecoratorSinus(Generator* n_generator,unsigned int n_T, double n_A):Decorator(n_generator),m_T(n_T),m_A(n_A){  
}
DecoratorSinus::~DecoratorSinus(){}

double DecoratorSinus::generuj(){
double val = Decorator::generuj();
  val+= m_A*std::sin(2* M_PI *1.0/this->m_T * this->m_licznik_wywolan);
  if(this->m_licznik_wywolan >=this->m_T-1){
    this->m_licznik_wywolan = 0;
  }else{
    this->m_licznik_wywolan++;
  }
  return val;
}


DecoratorSzum::DecoratorSzum(Generator* n_generator,double n_stddev ):Decorator(n_generator){  
   this->distribution = std::normal_distribution<double>(M_mean, n_stddev);
}

DecoratorSzum::~DecoratorSzum(){}

double DecoratorSzum::generuj(){
	double val = Decorator::generuj();
  val +=  this->distribution(this->generator);
  return val;
}


DecoratorDelay::~DecoratorDelay(){}

DecoratorDelay::DecoratorDelay(Generator* n_generator,unsigned int n_T0 ):Decorator(n_generator),m_T0(n_T0){  
}

double DecoratorDelay::generuj(){
	double val = Decorator::generuj();
  this->m_licznik_wywolan++;
  if(this->m_licznik_wywolan<=this->m_T0){
     return 0.0;
  }else{
    return val;
  }
}


DecoratorNasycenie::DecoratorNasycenie(Generator* n_generator,double n_A):Decorator(n_generator),m_A(n_A){  
}

DecoratorNasycenie::~DecoratorNasycenie(){}
double DecoratorNasycenie::generuj(){
	double val = Decorator::generuj();
  if(val>=this->m_A ){
     return this->m_A;
  }else if(val <= -(this->m_A)){
    return -this->m_A;
  }else {
    return val;
  }
}
