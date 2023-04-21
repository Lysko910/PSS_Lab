#pragma once
#include "SISO.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <functional>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <deque>
#include <map>
#include <random>
 /**
  * \class ARX
  * @brief Klasa modeulujca obiekty dyskretne o strukturze ARX
  */

class ARX :
    public SISO
{
public:
    /**
     * @brief Konstruktor z parmetrami domniemanymi
     * @see ARX(std::vector<double> n_A ={1}, std::vector<double> n_B={0}, unsigned int n_k = 0, double n_var = 0.0);
     * @param m_A Wektor parametrow A modelu ARX
     * @param m_B Wektor parametrow B modelu ARX
     * @param m_k Opoznienie sygnau 
     * @param m_var Wariancja sygnalu
     */
    ARX(std::vector<double> n_A ={1}, std::vector<double> n_B={0}, unsigned int n_k = 0, double n_var = 0.0);
    /**
     * @brief Konstruktor kopiujacy
     */
    ARX(const ARX& n_arx);
     /**
     * @brief Destruktor
     */
    ~ARX();
     /**
     * @brief operator przypisania
     */
    ARX& operator=(const ARX& n_arx);
    /**
     * @brief operator<< przesania do strumienia zwraca 
     */
    friend std::ostream& operator<<(std::ostream& ss, const ARX& n_arx);
    /**
     * @brief Funkcja do jednokrokowej symulacji odpowiedzi obiektu dyksretnego
	 * @param  n_U Wartosc wejsciowa na obiekt dyskretny
     * @return Odpowiedz obiektu dyskretnego
     */
    double symuluj(double n_Ui) override;
    void writeConfig(std::string nazwa_config= "") override;
	void readConfig(std::string nazwa_config= "") override;

    /** \name funkcje get()
    *@{
    */
    /**
     * \get A
     *
     * pobiera wektor parametrow A modelu ARX
     *
     * \return Obecna wartosci parametrow A
     */
    std::vector<double> get_A() const
    {
        return  this->m_A;
    };
    /**
     * \get B
     *
     * pobiera wektor parametrow B modelu ARX
     *
     * \return Obecna wartosci parametrow B
     */
    std::vector<double> get_B() const
    {
        return this->m_B;
    };
    /**
     * \get U
     *
     * pobiera i zwarca wektor probek sterowania
     *
     * \return Obecne wartosci wektora U
     */
    std::deque<double> get_U() const
    {
        return this->m_U;
    };
    /**
     * \get Y
     *
     * pobiera i zwarca wektor probek Odpowiedzi obiektu
     *
     * \return Obecne wartosci wektora Y
     */
    std::deque<double> get_Y() const
    {
        return this->m_Y;
    };
    /**
     * \get k
     *
     * pobiera i zwarca wartosc opoznienia modelu
     *
     * \return Obecne wartosci opoznienia k
     */
    unsigned int get_k() const
    {
        return this->m_k;
    };
    /**
     * \get var
     *
     * pobiera i zwarca wartosc variancji sygnalu modelu
     *
     * \return Obecne wartosci wariancji sygnalu var 
     */
    double get_var() const
    {
        return this->m_var;
    };
    /** @} */

     /** \name funkcje set()
    *@{
    */
    /**
     * \set m_A
     *
     * Ustawia wartosci wielomianu A
     *
     * \param n_A Wielomian A modelu ARX
     */
    void set_A(std::vector<double> n_A)
    {
        this->m_A = n_A;
        this->m_dA = this->m_A.size();
        std::deque<double> dY(this->m_dA, 0.0);
        this->m_Y = dY;
    };
      /**
     * \set m_B
     *
     * Ustawia wartosci wielomianu B
     *
     * \param n_B Wielomian B modelu ARX
     */
    void set_B(std::vector<double> n_B)
    {
        this->m_B = n_B;
        this->m_dB = this->m_B.size();
        std::deque<double> dU(this->m_dB + this->m_k, 0.0);
        this->m_U = dU;
    };
    /**
     * \set m_k
     *
     * Ustawia wartosci opoznienia k
     *
     * \param n_k opoznienie sygnau dyskretnego k
     */
    void set_k(unsigned int n_k)
    {
        this->m_k = n_k;
        std::deque<double> dU(this->m_dB + this->m_k, 0.0);
        this->m_U = dU;
    };
    /**
     * \set m_var
     *
     * Ustawia wartosci wariancji sygnalu dyskretnego
     *
     * \param n_var wariancja sygnalu dyskretnego
     */
     void set_var(double n_var)
    {
        this->m_var = n_var;
    };
    /** @} */

private:   
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
    // nazwa obiektu 
    std::string m_nazwaObiektu;
    // licznik obiektow klasy ARX
    static int m_liczbaObiektow;
    /// probki sygnalu sterujacego
    std::deque<double> m_U;
    /// probki odpowiedzi modelu ARX
	std::deque<double> m_Y;
    /** @name Parametry modelu ARX
    * @{
    */
    /// Wektor parametrow A modelu ARX
    std::vector<double> m_A;
    /// Wektor parametrow B modelu ARX
    std::vector<double> m_B;
    /// opoznienie probek dyskretnych w modelu ARX
    unsigned int m_k;
    /// Stopien Licznika modelu ARX
    unsigned int m_dB;
    /// Stopie mianownika modelu ARX
    unsigned int m_dA;
    /// wariancja szumu odpowiedzi modelu ARX
    double m_var;
   /** @} */
};
