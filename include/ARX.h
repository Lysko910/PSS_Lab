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

class ARX :
    public SISO
{
public:
    ARX(std::vector<double> n_A ={1}, std::vector<double> n_B={0}, unsigned int n_k = 0, double n_var = 0.0);
    ARX(const ARX& n_arx);
    ~ARX();
    ARX& operator=(const ARX& n_arx);
    friend std::ostream& operator<<(std::ostream& ss, const ARX& n_arx);

    double symuluj(double n_Ui) override;
    virtual void writeConfig() override;
	virtual void readConfig() override;

    //get "inline"
    std::vector<double> get_A() const
    {
        return  this->m_A;
    };

    std::vector<double> get_B() const
    {
        return this->m_B;
    };

    std::deque<double> get_U() const
    {
        return this->m_U;
    };

    std::deque<double> get_Y() const
    {
        return this->m_Y;
    };

    unsigned int get_k() const
    {
        return this->m_k;
    };

    double get_var() const
    {
        return this->m_var;
    };

    //set "inline"
    void set_A(std::vector<double> n_A)
    {//trzeba zmieni� m_Y
        this->m_A = n_A;
        this->m_dA = this->m_A.size();
        std::deque<double> dY(this->m_dA, 0.0);
        this->m_Y = dY;
    };

    void set_B(std::vector<double> n_B)
    {//trzeba zmieni� m_U
        this->m_B = n_B;
        this->m_dB = this->m_B.size();
        std::deque<double> dU(this->m_dB + this->m_k, 0.0);
        this->m_U = dU;
    };

    void set_k(unsigned int n_k)
        //trzeba zmieni� m_U
    {
        this->m_k = n_k;
        std::deque<double> dU(this->m_dB + this->m_k, 0.0);
        this->m_U = dU;
    };

private:
    template <typename T>
    std::string vecorToString(std::vector<T> n_v){
        std::string result = std::accumulate(n_v.begin(), n_v.end(),std::string{},
        [](const std::string& s, T d){return s.empty() ? std::to_string(d) : s + "," + std::to_string(d);});
        return result;
    };

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



    //wielomiany modelu ARX
    std::vector<double> m_A;
    std::vector<double> m_B;
    //parametry modelu ARX
    unsigned int m_k;
    unsigned int m_dB;
    unsigned int m_dA;
    double m_var;
    std::deque<double> m_U;
	std::deque<double> m_Y;

};

