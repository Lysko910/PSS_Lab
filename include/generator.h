#pragma once
#include <cmath>
#include <random>

/**
  * \class Generator (component)
  * @brief Klasa interface dla genertorow i ich dekoratorow
  */
class Generator{
public:
  /**
     * @brief Konstruktor
     */
Generator();
  /**
     * @brief Destruktor
     */
virtual ~Generator();
  /**
     * @brief Metoda wirtualna, interefej dla generatorow
     * metoda ma generowac odpowiedni sygnal dyskretny
     */
virtual double generuj() = 0;
};

/**
  * \class Generator (concrete_component)
  * @brief Klasa podstawowego generatora, generujacego wartosc stala
  */
class GeneratorConst: public Generator{
private:
double m_val;
public:
  /**
     * @brief Destruktor
     */
~GeneratorConst();
 /**
     * @brief Konstruktor z parmetrem domniemanym
     * @see GeneratorConst(double n_val = 0.0)
     * @param n_val wartosc stalej zwracanej przez generator
     * */
GeneratorConst(double n_val = 0.0);
/**
     * @brief funkja generujaca probke sygnalu 
     * @return wartosc stala, zalena od konstruktora
     */
double generuj()override;

};

/**
  * \class Decorator (interface do dekoratorw)
  * @brief Klasa interface dla dekoratorow implementuje bazowy generator
  * */
class Decorator :public Generator{
protected:
  Generator* m_generator;
  unsigned int m_licznik_wywolan = 0;
public:
 /**
     * @brief Konstruktor
     * @param  wskanik na generator, ktory bedzie dekorowany
     */
  Decorator(Generator* n_generator);
   /**
     * @brief Destruktor
     */
 ~Decorator();
 /**
     * @brief generuje wartosc bazowego generatora
     * @return wartosc stala z bazowego generatora
     */
  double generuj()override;
	
};

/**
  * \class Decorator sygnalu prostokatnego
  * @brief Klasa implementujaca konkretny dekorator dodajacy sygnal prostokatny
  * */
class DecoratorProstokat:public Decorator{
private:
int m_T = 1;
double m_wyp; 
public:
 /**
     * @brief Konstruktor z parmetrem domniemanym
     * @see DecoratorProstokat(Generator* n_generator, int n_T,double n_wyp = 0.5)
     * @param n_generator wskaznik na generator do udekorowania
     * @param n_T okres sygnalu
     * @param n_wyp wypelnienie sygnalu (0.0 - 1.0)
     * */
DecoratorProstokat(Generator* n_generator, int n_T,double n_wyp = 0.5);
/**
     * @brief Destruktor
* */
~DecoratorProstokat();
/**
     * @brief generuje wartosc dyskretna sygnalu prostokatnego zalezna od liczby wywolan
     * @return wartosc zalezna od generatora bazowego, parametrow dekoratora o krztalcie sygnalu prostokatnego
     */
double generuj()override;

};

/**
  * \class Decorator sygnalu sinusoidalnego
  * @brief Klasa implementujaca konkretny dekorator dodajacy sygnal sinusoidalny
  * */
class DecoratorSinus:public Decorator{
private:
double m_A = 1.0;
unsigned int m_T = 0;
public:
 /**
     * @brief Konstruktor z parmetrem domniemanym
     * @see DecoratorSinus(Generator* n_generator,unsigned int n_T, double n_A)
     * @param n_generator wskaznik na generator do udekorowania
     * @param n_T okres sygnalu
     * @param n_A amplituda sygnalu
     * */
DecoratorSinus(Generator* n_generator,unsigned int n_T, double n_A);
/**
     * @brief Destruktor
* */
~DecoratorSinus();
/**
     * @brief generuje wartosc dyskretna sygnalu sinusoidalnego zalezna od liczby wywolan
     * @return wartosc zalezna od generatora bazowego, parametrow dekoratora o krztalcie sygnalu sinusoidalnego
     */
double generuj()override;

};

/**
  * \class Decorator szumu
  * @brief Klasa implementujaca konkretny dekorator dodajacy szum do sygnalu generatora
  * */
class DecoratorSzum:public Decorator{
private:
std::mt19937 generator{std::random_device{}()};
std::normal_distribution<double> distribution;
const double M_mean = 0.0;
public:
 /**
     * @brief Konstruktor z parmetrem domniemanym
     * @see DecoratorSzum(Generator* n_generator,double n_stddev =1.0)
     * @param n_generator wskaznik na generator do udekorowania
     * @param n_stddev  odchylenie standardowe szumu
     * */
DecoratorSzum(Generator* n_generator,double n_stddev =1.0);
/**
     * @brief Destruktor
* */
~DecoratorSzum();

/**
     * @brief generuje wartosc dyskretna szumu dla sygnalu o rozkladzie normalnym
     * @return wartosc zalezna od generatora bazowego, parametrow dekoratora o charakterze losowym
     */
double generuj()override;
};

/**
  * \class Decorator opozniajacy
  * @brief Klasa implementujaca konkretny dekorator wprowadzajaca opoznienie do sygnalu
  * */
class DecoratorDelay:public Decorator{
private:
    unsigned int m_T0;
public:
 /**
     * @brief Konstruktor z parmetrem domniemanym
     * @see  DecoratorDelay(Generator* n_generator,unsigned int n_T0 = 0)
     * @param n_generator wskaznik na generator do udekorowania
     * @param n_T0  liczba probek opoznienia
     * */
    DecoratorDelay(Generator* n_generator,unsigned int n_T0 = 0);
    /**
     * @brief Destruktor
* */
    ~DecoratorDelay();

/**
     * @brief generuje wartosc generatora z zadanym opoznieniem 
     * @return probka sygnalu generatora po czasie T0, przed tym wartosc 0
     */
    double generuj()override;

};

/**
  * \class Decorator nasycajacy
  * @brief Klasa implementujaca konkretny dekorator wprowadzajaca nasycenie sygnalu
  * */
class DecoratorNasycenie:public Decorator{
private:
    double m_A;
public:
/**
     * @brief Konstruktor z parmetrem domniemanym
     * @see  DecoratorNasycenie(Generator* n_generator,double n_A)
     * @param n_generator wskaznik na generator do udekorowania
     * @param n_A wartosc ograniczenie z gory i z dolu
     * */
    DecoratorNasycenie(Generator* n_generator,double n_A);
    /**
     * @brief Destruktor
* */
    ~DecoratorNasycenie();
    /**
     * @brief generuje wartosc generatora z ograniczniem wartosci do n_A
     * @return wartosc generatora lub n_A lub -n_A, zalenie od wartosci generatora 
     */
    double generuj()override;

};