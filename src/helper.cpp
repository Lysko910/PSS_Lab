#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <fstream>
#include <sstream>
#include <algorithm>

template <typename T>
void plotToFile(std::vector<T> V1, std::string f_name = "results.txt") {
    std::ofstream myfile;
    myfile.open(f_name);
    for (auto x : V1) {
        myfile << x << std::endl;
    }
    myfile.close();
    std::cout << "Data written to file!!" << std::endl;
};

template <typename T>
void plotToFile(std::vector<T> V1, std::vector<T> V2, std::string f_name = "results.txt") {
    std::ofstream myfile;
    myfile.open(f_name);
    int n = V1.size() < V2.size() ? V2.size() : V1.size();
    for (int i = 0; i < n; i++) {
        if (i < V1.size()) {
            myfile << V1[i] << " ";
        }
        else {
            myfile << "_" << " ";
        }
        if (i < V2.size()) {
            myfile << V2[i] << " ";
        }
        else {
            myfile << "_" << " ";
        }
        myfile << std::endl;

    }
    myfile.close();
    std::cout << "Data written to file!!" << std::endl;
};


template <typename T>
void plotToFile(std::vector<T> V1, std::vector<T> V2, std::vector<T> V3, std::string f_name = "results.txt") {
    std::ofstream myfile;
    myfile.open(f_name);
    int n = V1.size() < V2.size() ? V2.size() : V1.size();
    n = n < V3.size() ? V2.size() : n;
    for (int i = 0; i < n; i++) {
        if (i < V1.size()) {
            myfile << V1[i] << " ";
        }
        else {
            myfile << "_" << " ";
        }
        if (i < V2.size()) {
            myfile << V2[i] << " ";
        }
        else {
            myfile << "_" << " ";
        }
        if (i < V3.size()) {
            myfile << V3[i] << " ";
        }
        else {
            myfile << "_" << " ";
        }
        myfile << std::endl;

    }
    myfile.close();
    std::cout << "Data written to file!!" << std::endl;
};


/**
     * @brief Funckja zmieniajaca wektor dowolnego typu na string
     */
    template <typename T>
    std::string vecorToString(std::vector<T> n_v){
        std::string result = std::accumulate(n_v.begin(), n_v.end(),std::string{},
        [](const std::string& s, T d){return s.empty() ? std::to_string(d) : s + "," + std::to_string(d);});
        return result;
    };
    /**
     * @brief Funckja zmieniajaca string na wektor
     */
    template<typename T>
    std::vector<T> stringToVector(const std::string& n_str) {
        std::vector<T> v;
        std::istringstream iss(n_str);
        std::string token;
        while (std::getline(iss, token, ',')) {
            T value = std::stod(token);
            v.push_back(value);
        }
        return v;
    };