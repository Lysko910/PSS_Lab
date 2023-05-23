#pragma once
#include "SISO.h"
/**
 * Klasa bazowa dla struktur, jako interface dla objektow i kompozytow
 * 
 **/
class Komponent{
/**
 * @var Component
 **/
protected:
    Komponent * m_komponent_bazowy;
    public:
    /**
         * @brief Konstruktor
         */
    Komponent(){};    
    /**
         * @brief Konstruktor
         */
    virtual ~Komponent(){};
    /**
         * \set m_komponet_bazowy
         *
         * Ustawia wartosci bazowego komponentu w strukturze 
         *
         * \param n_komponent_bazowy 
         */
    void setBazowy(Komponent * n_komponent_bazowy){
        this->m_komponent_bazowy = n_komponent_bazowy;
    }
    /**
         * \get m_komponet_bazowy
         *
         * Wzwraca wskaznik na komponent bazowy
         *
         * \return *m_komponet_bazowy 
         */
    Komponent* getBazowy()const{
        return this->m_komponent_bazowy;
    } 
    /**
         * @brief dodaj 
         * dodje element do kompozytu
         */
    virtual void dodaj(Komponent * n_komponent){}
    /**
         * @brief usun
         * usuwa element z kompozytu
         */
    virtual void usun(Komponent * n_komponent){}
    /**
         * @brief czyToKompozyt
         * sprawdza czy obiekt jest kompozytem czy komponentem
         */
    virtual bool czyToKompozyt()const{
        return false;
    }
     /**
     * @brief Funkcja do jednokrokowej symulacji odpowiedzi obiektu dyksretnego
	 * @param  n_U Wartosc wejsciowa na obiekt dyskretny
     * @return Odpowiedz obiektu dyskretnego
     */
	virtual double symuluj(double n_U) = 0;

};

/**
 * Klasa Kompozyt, struktura mogaca zawierac wiele elementow
 **/
class Kompozyt: public Komponent{
    protected:
    std::vector<Komponent* > m_komponenty_pochodne;

    public:
    void dodaj(Komponent * n_komponent)override{
        this->m_komponenty_pochodne.push_back(n_komponent);
        n_komponent->setBazowy(this);
    }

    void usun(Komponent * n_komponent)override{
        this->m_komponenty_pochodne.pop_back(n_komponent);
        n_komponent->setBazowy(nullptr);

    }

    bool czyToKompozyt()const{
        return true;
    }

};