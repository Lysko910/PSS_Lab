#include "ARX.h"

int ARX::m_liczbaObiektow = 0;

ARX::ARX(std::vector<double> n_A , std::vector<double> n_B , unsigned int n_k ,double n_var)
	:m_B(n_B), m_A(n_A), m_k(n_k), m_var(n_var)
{
	this->m_dA = n_A.size();
	this->m_dB = n_B.size();

	std::deque<double> dU(this->m_dB + this->m_k, 0.0);
	this->m_U = dU;
	std::deque<double> dY(this->m_dA, 0.0);
	this->m_Y = dY;
	++this->m_liczbaObiektow;
	this->m_nazwaObiektu ="ARX_"+std::to_string(this->m_liczbaObiektow);
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
	++this->m_liczbaObiektow;
	this->m_nazwaObiektu ="ARX_"+std::to_string(this->m_liczbaObiektow);
}
//destruktor
ARX::~ARX()
{	
	--this->m_liczbaObiektow;
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
		this->m_nazwaObiektu =n_arx.m_nazwaObiektu;
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
	ss << n_arx.m_nazwaObiektu <<std::endl<<
		"dA = " << n_A.size() << " dB = " << n_B.size()
		<< " k = " << n_arx.get_k() << " var(e) = " << n_arx.get_var() << "\n"
		<< "wielomian A: [ " << stringA << " ] " << "\n"
		<< "wielomian B: [ " << stringB << " ] " << std::endl;

	return ss;
}
//funkcja symuluj�ca 1 krok modelu
double ARX::symuluj(double n_Ui)
{
	std::normal_distribution<double> noise{0.0,std::sqrt(std::fabs(this->m_var))};
	std::default_random_engine silnik(std::random_device{}());
	double n_ei = noise(silnik);

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

void ARX::writeConfig(std::string nazwa_config){
//usawienie danych do wpisania
std::map<std::string, std::string> config = {
    {"A", vecorToString(this->get_A())},
    {"B", vecorToString(this->get_B())},
    {"k", std::to_string(this->get_k())},
    {"var_e", std::to_string(this->get_var())}};
	
	if(nazwa_config.empty()) nazwa_config = this->m_nazwaObiektu; 

	nazwa_config= "["+nazwa_config+"]";

	std::vector<std::string> help_saver;
    std::string line;
	bool found = false;
	bool save = false;
// otwarcie pliku w celu wyczyszczenia 
	std::fstream file("config.ini", std::ios::in | std::ios::out);
    if (file) {
    
        while (std::getline(file, line)) {
            //poszukiwanie odpowiedniego miejsca
			if (line == nazwa_config) {
                found = true;
            } else if (found && line.find("=") != std::string::npos) {
				//czyszczenie sekcji
                file.seekp(-line.length()-1, std::ios::cur); 
                file << std::string(line.length(), ' '); 
            }else if (found && line.find("[") != std::string::npos){
				save = true;
			}
			if(save && !line.empty())
				help_saver.push_back(line);
        }
		file.close();
    } else {
        std::cerr << "Error: could not open file 'config.ini' for reading" << std::endl;
    }

//otwarcie pliku do zapisania danych
	std::fstream file2("config.ini", std::ios::in | std::ios::out);
	if (file2) {
		if (found) { // zmiana sekcji istniejacej
			// przejscie do poczatku sekcji
				while (std::getline(file2, line)) {
					if (line == nazwa_config) {
					break;
					}
				}
			// wpisanie danych
				for (const auto& entry : config) {
				file2 << entry.first << "=" << entry.second << std::endl;
				}
				file2 << std::endl;
				for (const auto& string_help : help_saver) {
				file2 << string_help <<std::endl;
				}

		} else { // zapisn nowych danych na koncu pliku
			// Append new data
			file2.clear();
			file2.seekp(0, std::ios::end);
			file2 << nazwa_config << std::endl;
				for (const auto& entry : config) {
				file2 << entry.first << "=" << entry.second << std::endl;
				}
		}
	
		file2.close();
	} else {
        std::cerr << "Error: could not open file 'config.ini' for reading" << std::endl;
    }
}

void ARX::readConfig(std::string nazwa_config){
	std::map<std::string, std::string> config;
    std::ifstream file("config.ini");

	if(nazwa_config.empty()) nazwa_config = this->m_nazwaObiektu; 

	nazwa_config= "["+nazwa_config+"]";
	
    if (file)
    {	bool found = false;
        std::string line;
        while (std::getline(file, line))
        {	if (line == nazwa_config) {
            found = true;
            continue;
			}
		size_t pos = line.find("[");
		if((pos != std::string::npos)&& found){
			break;
		}	
		if(found){
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(std::getline(iss, key, '='), value))
            {
                config[key] = value;
            }
        }
		}
    }
    else
    {
        std::cerr << "Error: could not open file 'config.ini' for reading" << std::endl;
    }
	std::string temp = config.at("A"); 
	this->set_A(this->stringToVector<double>(config.at("A")));
	this->set_B(this->stringToVector<double>(config.at("B")));
	this->set_k(std::stoul(config.at("k")));
	this->m_var=std::stod(config.at("var_e"));
	
	
}
