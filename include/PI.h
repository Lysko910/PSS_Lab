#pragma once
#include "SISO.h"


 /**
  * \class PI
  * @brief Klasa modeulujca Regulator PI
  */
class PI:virtual public SISO{
public:
    /**
     * @brief Konstruktor z parmetrami domniemanymi
     * @see PI( double n_w= 1.0,double n_Kp = 2.0,double n_Ti = 1e3, double n_dt=0.1)
     * @param n_w wartosc zadana
     * @param n_Kp wzmocnienie
     * @param n_Ti stla calkowania
     * @param n_dt czas probkowania
     */
    PI( double n_w= 1.0,double n_Kp = 2.0,double n_Ti = 1e3, double n_dt=0.1);
     /**
     * @brief Destruktor
     */
    ~PI();
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

protected:
    /**
     * @brief oblicz czesc proporcjonalna
     * @param n_Ei
     */
    double proportional(double n_Ei);
    /**
     * @brief oblicz czesc calkujaca
     * @param n_Ei
     */
    double integral(double n_Ei);
    /// wartosc zadana
    double m_w;
    double suma_Ei = 0.0;
/** @name Parametry mregulatora PI
    * @{
    */
    double m_Kp;
    double m_Ti;
    double m_dt;
    /** @} */
    double m_MAX =100.0;
    double m_MIN = 0.0;
    
     /**
     * @brief Funckja zmieniajaca wektor dowolnego typu na string
     */
    template <typename T>
    std::string vecorToString(std::vector<T> n_v){
        std::string result = std::accumulate(n_v.begin(), n_v.end(),std::string{},
        [](const std::string& s, T d){return s.empty() ? std::to_string(d) : s + "," + std::to_string(d);});
        return result;
    };
    /**
     * @brief Funckja zmieniajaca string na wektor
     */
    template<typename T>
    std::vector<T> stringToVector(const std::string& n_str) {
        std::vector<T> v;
        std::istringstream iss(n_str);
        std::string token;
        while (std::getline(iss, token, ',')) {
            T value = std::stod(token);
            v.push_back(value);
        }
        return v;
    };
};