#pragma once

#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct info
{
    string vardas, pavarde;
    double egz_rezultatas, galutinis, mediana, galutinis_mediana;
    vector<double> nd_rezultatai;
};

unsigned int zodziu_stringe(string const& str);
void Skaityk_faila(vector<info>& studentas, int* pazymiu_sk);
bool pagalba_rusiavimui(const info& kaire, const info& desine);
void Rusiuok(vector<info>& studentas);
void Galutinis_balas(vector<info>& studentas);
void Mediana(vector<info>& studentas);
void Rasyk_i_faila(vector<info>& studentas, int pazymiu_sk);