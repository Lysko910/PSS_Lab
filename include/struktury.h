#pragma once
#include <vector>

/**
 * Klasa bazowa dla struktur, jako interface dla objektow i kompozytow
 * 
 **/
class Komponent{
    public:
    /**
         * @brief Konstruktor
         */
     Komponent();
    /**
         * @brief Destruktor
         */
    virtual ~Komponent();
    /**
         * \set m_komponet_bazowy
         *
         * Ustawia wartosci bazowego komponentu w strukturze 
         *
         * \param n_komponent_bazowy 
         */
    void setBazowy(Komponent * n_komponent_bazowy);
    /**
         * \get m_komponet_bazowy
         *
         * Wzwraca wskaznik na komponent bazowy
         *
         * \return *m_komponet_bazowy 
         */
    Komponent* getBazowy()const;
    /**
         * @brief dodaj 
         * dodje element do kompozytu
         */
    virtual void dodaj(Komponent * n_komponent);
    /**
         * @brief usun
         * usuwa element z kompozytu
         */
    virtual void usun(Komponent * n_komponent);
    /**
         * @brief czyToKompozyt
         * sprawdza czy obiekt jest kompozytem czy komponentem
         */
    virtual bool czyToKompozyt()const;
     /**
     * @brief Funkcja do jednokrokowej symulacji odpowiedzi obiektu dyksretnego
	 * @param  n_U Wartosc wejsciowa na obiekt dyskretny
     * @return Odpowiedz obiektu dyskretnego
     */
	virtual double symuluj(double n_U) = 0;
     /**
 * @var Component
 **/
protected:
    Komponent * m_komponent_bazowy;
};

/**
 * Klasa Kompozyt, struktura mogaca zawierac wiele elementow
 **/
class Kompozyt: public Komponent{
    protected:
    std::vector<Komponent *> m_komponenty_pochodne;

    public:
    void dodaj(Komponent * n_komponent)override;

    void usun(Komponent * n_komponent)override;

    bool czyToKompozyt()const;
};

/**
 * Klasa implementujaca konkretna strukture polaczenia rownoleglego
 **/
class StrukturaRownolegla: public Kompozyt{
public:
     /**
     * @brief Funkcja do jednokrokowej symulacji odpowiedzi obiektu dyksretnego na obiektach w strukturze rownoleglej
	 * @param  n_U Wartosc wejsciowa na struktrue rownolegla 
     * @return Odpowiedz struktury rownoleglej obiektow dyskretnych
     */
    double symuluj(double n_U)override;
};
/**
 * Klasa implementujaca konkretna strukture polaczenia szeregowego
 **/
class StrukturaSzeregowa: public Kompozyt{
public:
/**
     * @brief Funkcja do jednokrokowej symulacji odpowiedzi obiektu dyksretnego na obiektach w strukturze szeregowej
	 * @param  n_U Wartosc wejsciowa na struktrue szeregowa 
     * @return Odpowiedz struktury szeregowej obiektow dyskretnych
     */
    double symuluj(double n_U)override;

};