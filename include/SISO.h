#pragma once
#include <string>
class SISO
{
public:
	SISO(){};
	virtual ~SISO(){};
	virtual double symuluj(double) = 0;
	virtual void writeConfig(std::string nazwa_config = "") = 0;
	virtual void readConfig(std::string nazwa_config = "") = 0;
};

