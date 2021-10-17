
#include "header.h"
#include "Source1.cpp"

using namespace std;


int main()
{
    int pazymiu_sk;
    vector<info> studentas;
    
    Skaityk_faila(studentas, &pazymiu_sk);
    Galutinis_balas(studentas);
    Mediana(studentas);
    Rusiuok(studentas);
    Rasyk_i_faila(studentas,pazymiu_sk);
    
    return 0;
}

