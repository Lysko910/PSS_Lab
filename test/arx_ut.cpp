#include <gtest/gtest.h>
#include "../include/ARX.h"
#include <cmath>


bool porownanieSekwencji(std::vector<double>& spodz, std::vector<double>& fakt)
{
	constexpr double TOL = 1e-3;	// tolerancja dla por�wna� zmiennoprzecinkowych
	bool result = fakt.size() == spodz.size();
	for (int i = 0; result && i < fakt.size(); i++)
		result = fabs(fakt[i] - spodz[i]) < TOL;
	return result;
}

// my first test
TEST(TestARX, test_ARX_brakPobudzenia) {
    ARX instancjaTestowa({ -0.4 }, { 0.6 }, 1, 0);
    constexpr size_t LICZ_ITER = 30;
    std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu (tu same 0)
    std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy (tu same 0)
    std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

	// Symulacja modelu:
    for (int i = 0; i < LICZ_ITER; i++){
        faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);
    }
    EXPECT_EQ(1, porownanieSekwencji(spodzSygWy,faktSygWy));
}

TEST(TestARX, test_ARX_skokJednostkowy_2) {

    // Przygotowanie danych:
    ARX instancjaTestowa({ -0.4 }, { 0.6 }, 2, 0);
    constexpr size_t LICZ_ITER = 30;
    std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu, 
    std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy
    std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

    // Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
    for (int i = 0; i < LICZ_ITER; i++)
        sygWe[i] = !!i;
	spodzSygWy = { 0, 0, 0, 0.6, 0.84, 0.936, 0.9744, 0.98976, 0.995904, 0.998362, 0.999345, 0.999738, 0.999895, 0.999958, 0.999983, 0.999993, 0.999997, 0.999999, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    // Symulacja modelu:
    for (int i = 0; i < LICZ_ITER; i++)
        faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

    EXPECT_EQ(1, porownanieSekwencji(spodzSygWy,faktSygWy));
}

TEST(TestARX, test_ARX_skokJednostkowy_3) {

    // Przygotowanie danych:
    ARX instancjaTestowa({ -0.4,0.2 }, { 0.6, 0.3 }, 2, 0);
    constexpr size_t LICZ_ITER = 30;
    std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu, 
    std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy
    std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

    // Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
    for (int i = 0; i < LICZ_ITER; i++)
        sygWe[i] = !!i;
    spodzSygWy = { 0, 0, 0, 0.6, 1.14, 1.236, 1.1664, 1.11936, 1.11446, 1.12191, 1.12587, 1.12597, 1.12521, 1.12489, 1.12491, 1.12499, 1.12501, 1.12501, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125 };

    // Symulacja modelu:
    for (int i = 0; i < LICZ_ITER; i++)
        faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

    EXPECT_EQ(1, porownanieSekwencji(spodzSygWy,faktSygWy));
}
