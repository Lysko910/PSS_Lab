#pragma once
#include "PD.h"
#include "PI.h"

class PID: public PI, public PD{
public:
PID( double n_w= 1.0,double n_Kp = 2.0 ,double n_Ti = 1e6,double n_Td = 0.0, double n_dt=0.1);
~PID();

double symuluj(double n_Yi) override;
void writeConfig(std::string nazwa_config= "") override;
void readConfig(std::string nazwa_config= "") override;

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
