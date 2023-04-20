
#include <iostream>
#include "helper.cpp"
#include "../include/ARX.h"

using std::cout;
using std::cin;
using std::endl;

int main()
{	

	ARX arx({ -9.2 }, { 0.9}, 2, 0.0);
	arx.writeConfig();
	arx.readConfig();
	cout<<arx<<endl;

	arx.set_A({1.2, 4.1});
	arx.set_B({5.2, 2.0});
	arx.set_k(2);
	arx.set_var(4.0);
	arx.writeConfig();
	arx.readConfig();
	cout<<arx<<endl;

	arx.symuluj(0.0);
	arx.symuluj(1.0);
	arx.symuluj(1.0);
	arx.symuluj(1.0);

    return 0;
}
