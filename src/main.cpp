
#include <iostream>
#include <fstream>
#include <cmath>
#include "helper.cpp"
#include "../include/ARX.h"

#include <map>

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
	arx.writeConfig();
	arx.readConfig();
	cout<<arx<<endl;

    return 0;
}
