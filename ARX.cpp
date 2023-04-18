#include "ARX.h"

//konstruktor bezargumentowy
ARX::ARX()
	:m_B({}), m_A({}), m_k(0), m_var(0.0)
{
	this->m_dA = m_A.size();
	this->m_dB = m_B.size();

	std::deque<double> dU(this->m_dB + this->m_k, 0.0);
	this->m_U = dU;
	std::deque<double> dY(this->m_dA, 0.0);
	this->m_Y = dY;

	//std::cout << "ARX object constructed" << std::endl;
}
//konstruktor z inicjalizacj�
ARX::ARX(std::vector<double> n_A = {}, std::vector<double> n_B = {}, unsigned int n_k, double n_var)
	:m_B(n_B), m_A(n_A), m_k(n_k), m_var(n_var)
{
	this->m_dA = n_A.size();
	this->m_dB = n_B.size();

	std::deque<double> dU(this->m_dB + this->m_k, 0.0);
	this->m_U = dU;
	std::deque<double> dY(this->m_dA, 0.0);
	this->m_Y = dY;

	//std::cout << "ARX object constructed" << std::endl;
}
//konstruktor kopiuj�cy
ARX::ARX(const ARX& n_arx)
{//przepisanie parametr�w 
	this->m_A = n_arx.get_A();
	this->m_B = n_arx.get_B();
	//przepisanie parametr�w modelu
	this->m_k = n_arx.get_k();
	this->m_dA = this->m_A.size();
	this->m_dB = this->m_A.size();
	//przepisanie wielomian�w y,u ????
	this->m_Y = n_arx.get_Y();
	this->m_U = n_arx.get_U();
	//std::cout << "ARX object copied" << std::endl;
}
//destruktor
ARX::~ARX()
{

	//std::cout << "ARX object destructed" << std::endl;
}
// operator przypisania
ARX& ARX::operator=(const ARX& n_arx)
{
	if (this != &n_arx) {
		//przepisanie parametr�w 
		this->m_A = n_arx.m_A;
		this->m_B = n_arx.m_B;
		//przepisanie parametr�w modelu
		this->m_k = n_arx.m_k;
		this->m_dA = n_arx.m_dA;
		this->m_dB = n_arx.m_dB;
		//przepisanie wielomian�w y,u ????
		this->m_Y = n_arx.m_Y;
		this->m_U = n_arx.m_U;
		//std::cout << "ARX object assigned" << std::endl;

	}
	return *this;
}
//operator << - wypisuje wszystkie paramery Modelu
std::ostream& operator<<(std::ostream& ss, const ARX& n_arx)
{
	std::vector<double> n_A;
	std::vector<double> n_B;
	n_A = n_arx.get_A();
	n_B = n_arx.get_B();
	std::string stringA = "";
	std::for_each(n_A.begin(), n_A.end(), [&stringA](double value) {
		stringA += std::to_string(value) + " ";
		});
	std::string stringB = "";
	std::for_each(n_B.begin(), n_B.end(), [&stringB](double value) {
		stringB += std::to_string(value) + " ";
		});
	ss << "Model ARX:\n" <<
		"dA = " << n_A.size() << " dB = " << n_B.size()
		<< " k = " << n_arx.get_k() << " var(e) = " << n_arx.get_var() << "\n"
		<< "wielomian A: [ " << stringA << " ] " << "\n"
		<< " wielomian B: [ " << stringB << " ] " << std::endl;

	return ss;
}
//funkcja symuluj�ca 1 krok modelu
double ARX::symuluj(double n_Ui)
{
	;
	// w przysz�osci b��d/zak��cenie
	double n_ei = 0.0;

	// sprawdzenie rozmiaru  
	if (this->m_U.size() != this->m_dB + this->m_k ||
		this->m_Y.size() != this->m_dA) {
		std::cout << "Vectors size don't match!!" << std::endl;
		return -1e8;
	}
	//aktualizacja U 
	if (!this->m_U.empty()) this->m_U.pop_back();
	this->m_U.push_front(n_Ui);
	//uzupe�nienie B o op�znienie k
	std::vector<double> kB(this->m_k, 0.0);
	kB.insert(kB.end(), this->m_B.begin(), this->m_B.end());

	//r�wnanie r�nicowe
	double kBxU_part = std::inner_product(kB.begin(), kB.end(), this->m_U.begin(), 0.0);
	double AxY_part = std::inner_product(this->m_A.begin(), this->m_A.end(), this->m_Y.begin(), 0.0);
	double n_Yi = kBxU_part - AxY_part + n_ei;
	//aktualizacja Y
	if (!this->m_Y.empty()) this->m_Y.pop_back();
	this->m_Y.push_front(n_Yi);

	return n_Yi;
}



