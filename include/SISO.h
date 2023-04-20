#pragma once

class SISO
{
public:
	SISO(){};
	virtual ~SISO(){};
	virtual double symuluj(double) = 0;
	virtual void writeConfig() = 0;
	virtual void readConfig() = 0;
};

