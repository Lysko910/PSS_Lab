#include "../include/struktury.h"

// KOMPONENT
    Komponent::Komponent(){}

    Komponent::~Komponent(){}
  
    void Komponent::setBazowy(Komponent * n_komponent_bazowy){
        this->m_komponent_bazowy = n_komponent_bazowy;
    }
    Komponent* Komponent::getBazowy()const{
        return this->m_komponent_bazowy;
    } 
    
    void Komponent::dodaj(Komponent * n_komponent){}
  
    void Komponent::usun(Komponent * n_komponent){}
    
    bool Komponent::czyToKompozyt()const{
        return false;
    }
    // KOMPOZYT
    void Kompozyt::dodaj(Komponent * n_komponent){
        this->m_komponenty_pochodne.push_back(n_komponent);
        n_komponent->setBazowy(this);
    }

    void Kompozyt::usun(Komponent * n_komponent){
        this->m_komponenty_pochodne.pop_back();
        n_komponent->setBazowy(nullptr);

    }

    bool Kompozyt::czyToKompozyt()const{
        return true;
    }

    double StrukturaSzeregowa::symuluj(double n_U){
        double result = n_U;
        for ( Komponent *komp : this->m_komponenty_pochodne) {
                    result = komp->symuluj(result);
            }
        return result;
    }

    double StrukturaRownolegla::symuluj(double n_U){
        double result = 0;
        for ( Komponent *komp : this->m_komponenty_pochodne) {
                result += komp->symuluj(n_U);
            }
        return result;
    }
