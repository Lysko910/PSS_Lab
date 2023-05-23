#pragma once
#include "SISO.h"



 /**
  * \class PD
  * @brief Klasa modeulujca Regulator PD
  */
class PD:virtual public SISO{
public:
/**
     * @brief Konstruktor z parmetrami domniemanymi
     * @see PI(double n_Kp = 2.0,double n_Ti = 1e3, double n_dt=1.0)
     * @param n_Kp wzmocnienie
     * @param n_Td stla rozniczkowania
     * @param n_dt czas probkowania
     */
    PD(double n_Kp = 1.0 ,double n_Td = 0.0, double n_dt=1);
      /**
     * @brief Destruktor
     */
    ~PD();
    /**
     * @brief Funkcja do jednokrokowej symulacj sterowania 
	 * @param  n_Ei Wartosc wejsciowa na regulator(UCHYB regulacji )
     * @return sterowanie wypracowane przez regulator
     */
    double symuluj(double n_Ei) override;
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

protected:
/**
     * @brief oblicz czesc proporcjonalna
     * @param n_Ei
     */
    double proportional(double n_Ei);
    /**
     * @brief oblicz czesc rozniczkujaca
     * @param n_Ei
     */
    double derivative(double n_Ei);
    double m_prev_E = 0.0;
/** @name Parametry mregulatora PI
    * @{
    */
    double m_Kp;
    double m_Td;
    double m_dt;
    /** @} */
    double m_MAX =100.0;
    double m_MIN = 0.0;

};