
#include "PID.h"

PID::PID(double n_Kp ,double n_Ti ,double n_Td, double n_dt)
:PI(n_Kp,n_Ti,n_dt),PD(n_Kp,n_Td,n_dt){}

PID::~PID(){
}

double PID::symuluj(double n_Ei){
	// obliczanie sterowania 
    double U = PI::proportional(n_Ei) + PI::integral(n_Ei)+ PD::derivative(n_Ei);
    // ograniczenie sterowania 
	if(U  > PI::m_MAX){
       U  = PI::m_MAX;
    }else if(U < PI::m_MIN){
       U = PI::m_MIN;
    }
return U;
}

void PID::writeConfig(std::string nazwa_config){
//ustawienie danych do wpisania
std::map<std::string, std::string> config = {
    {"Kp", std::to_string(PI::m_Kp)},
    {"Td", std::to_string(PD::m_Td)},
    {"Ti", std::to_string(PI::m_Ti)},
    {"dt", std::to_string(PI::m_dt)}};

// sprawdzenie nazwy i przypisanie odpowiedniej w razie zmiany
	if(nazwa_config.empty()) nazwa_config = "PID"; 
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
void PID::readConfig(std::string nazwa_config){
std::map<std::string, std::string> config;
    std::ifstream file("config.ini");

// sprawdzenie nazwy i przypisanie odpowiedniej w razie zmiany
	if(nazwa_config.empty()) nazwa_config = "PID"; 
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
	PI::m_Kp =  std::stoul(config.at("Kp"));
	PI::m_Ti = std::stoul(config.at("Ti"));
   PD::m_Td = std::stoul(config.at("Td"));
	PI::m_dt = std::stoul(config.at("dt"));
}
