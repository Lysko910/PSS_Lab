#include "PI.h"


PI::PI( double n_w, double n_Kp, double n_Ti, double n_dt)
:m_Kp(n_Kp),m_Ti(n_Ti),m_dt(n_dt),m_w(n_w){}

PI::~PI(){}

double PI::proportional(double n_Ei){
    return this->m_Kp * n_Ei; 
}

double PI::integral(double n_Ei){
    this->suma_Ei += n_Ei;
    double Ui =( this->suma_Ei /this->m_Ti)* this->m_dt * this->m_Kp; 
    // anti windup na czesci calkujacej
    if(Ui >this->m_MAX){
        Ui = this->m_MAX;
    }else if(Ui<this->m_MIN){
        Ui = this->m_MIN;
    }
return Ui;
}

double PI::symuluj(double n_Yi){
    double Ei = this->m_w - n_Yi;
    double Ui = this->proportional(Ei) + this->integral(Ei);
    if(Ui  > this->m_MAX){
       Ui  = this->m_MAX;
    }else if(Ui < this->m_MIN){
       Ui = this->m_MIN;
    }
return Ui;
}

void PI::writeConfig(std::string nazwa_config){
//ustawienie danych do wpisania
std::map<std::string, std::string> config = {
    {"Kp", std::to_string(this->m_Kp)},
    {"Ti", std::to_string(this->m_Ti)},
    {"dt", std::to_string(this->m_dt)},
    {"w", std::to_string(this->m_w)}};

// sprawdzenie nazwy i przypisanie odpowiedniej w razie zmiany
	if(nazwa_config.empty()) nazwa_config = "PI"; 
	nazwa_config= "["+nazwa_config+"]";
//zmienne pomocnicze 
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
			// zapamietanie danych pod sekcja
			if(save && !line.empty())
				help_saver.push_back(line);
        }
		file.close();
    } else {
        std::cerr << "Could not open file 'config.ini'" << std::endl;
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
			// wpisanie dancyh ponizej wprowadzonej sekcji	
				file2 << std::endl;
				for (const auto& string_help : help_saver) {
				file2 << string_help <<std::endl;
				}

		} else { // zapisn nowych danych na koncu pliku
			file2.clear();
			file2.seekp(0, std::ios::end);
			file2 << nazwa_config << std::endl;
				for (const auto& entry : config) {
				file2 << entry.first << "=" << entry.second << std::endl;
				}
		}
	
		file2.close();
	} else {
        std::cerr << "Culd not open file 'config.ini'" << std::endl;
    }
}

// TO DO
void PI::readConfig(std::string nazwa_config){
std::map<std::string, std::string> config;
    std::ifstream file("config.ini");

// sprawdzenie nazwy i przypisanie odpowiedniej w razie zmiany
	if(nazwa_config.empty()) nazwa_config = "PI"; 
	nazwa_config= "["+nazwa_config+"]";
	
    if (file)
    {	bool found = false;
        std::string line;
		// szukanie odpowiedniej sekcji
        while (std::getline(file, line))
        {	if (line == nazwa_config) {
            found = true;
            continue;
			}
		size_t pos = line.find("[");
		if((pos != std::string::npos)&& found){
			break;
		}	
		// czytanie z sekcji
		if(found){
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(std::getline(iss, key, '='), value))
            {
                config[key] = value;
            }
        }
		else{
		// brak konfiguracji do odczytu
			std::cout<<"Config not found !!!"<<std::endl;
		}
		}
    }
    else
    {
        std::cerr << "Could not open file 'config.ini'" << std::endl;
    }
	//przepisanie danych z konfiguracji do obiektustd::stod(config.at("var_e"));
	this->m_Kp =  std::stoul(config.at("Kp"));
	this->m_Ti = std::stoul(config.at("Ti"));
	this->m_dt = std::stoul(config.at("dt"));
	this->m_w = std::stoul(config.at("w"));
}