#pragma once
#include <deque>
class SISO
{
public:
	SISO();
	virtual ~SISO();
	virtual double symuluj(double) = 0;
protected:
	//wielomiany pr�bek sygna��w
	std::deque<double> m_U;
	std::deque<double> m_Y;
};

