#pragma once
#include "SISO.h"
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <numeric>
#include <algorithm>
#include <deque>

class ARX :
    public SISO
{
public:
    ARX(std::vector<double> n_A ={}, std::vector<double> n_B={}, unsigned int n_k = 0, double n_var = 0.0);
    ARX(const ARX& n_arx);
    ~ARX();
    ARX& operator=(const ARX& n_arx);
    friend std::ostream& operator<<(std::ostream& ss, const ARX& n_arx);

    double symuluj(double n_Ui) override;
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

    unsigned int get_var() const
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

