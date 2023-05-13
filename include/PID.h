#pragma once
#include "PD.h"
#include "PI.h"

 /**
  * \class PID
  * @brief Klasa modeulujca Regulator PID
  */
class PID: public PI, public PD{
public:
    /**
     * @brief Konstruktor z parmetrami domniemanymi
     * @see PI( double n_w= 1.0,double n_Kp = 2.0,double n_Ti = 1e3, double n_dt=0.1)
     * @param n_w wartosc zadana
     * @param n_Kp wzmocnienie
     * @param n_Td stla rozniczkowania
     * @param n_dt czas probkowania
     */
PID( double n_w= 1.0,double n_Kp = 2.0 ,double n_Ti = 1e6,double n_Td = 0.0, double n_dt=0.1);
 /**
     * @brief Destruktor
     */
~PID();
 /**
     * @brief Funkcja do jednokrokowej symulacj sterowania 
	 * @param  n_Yi Wartosc wejsciowa na regulator
     * @return sterowanie wypracowane przez regulator
     */
double symuluj(double n_Yi) override;
/**
     * @brief wpisz konfiguracje do pliku config.ini
     * @param nazwa_config
     */
void writeConfig(std::string nazwa_config= "") override;
/**
     * @brief odczytaj konfiguracje z pliku config.ini
     * @param nazwa_config
     */
void readConfig(std::string nazwa_config= "") override;


};
