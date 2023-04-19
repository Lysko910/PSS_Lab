#pragma once
class SISO
{
public:
	SISO(){};
	virtual ~SISO(){};
	virtual double symuluj(double) = 0;
};

