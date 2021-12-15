
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <list>
#include <numeric>

using std::cout;
using std::cin;
using std::setprecision;
using std::fixed;
using std::setw;
using std::string;
using std::vector;
using std::endl;
using std::left;
using std::ifstream;
using std::getline;
using std::swap;
using std::ofstream;
using std::stringstream;
using std::ws;
using std::to_string;
using std::list;
using namespace std::chrono;

struct info
{
    string vardas, pavarde;
    double egz_rezultatas, galutinis, mediana, galutinis_mediana;
    vector<double> nd_rezultatai;
};

unsigned int zodziu_stringe(std::string const& str)
{
    stringstream stream(str);
    return (unsigned int)distance(std::istream_iterator<string>(stream), std::istream_iterator<string>());
}

void Sugeneruok_failus()
{
    int nd_skaicius = 5;
    const int failu_kiekis = 1;
    int studentu_skaicius[failu_kiekis] = { 10000000 };

    for (int x = 0; x < failu_kiekis;x++) {
        auto start = high_resolution_clock::now();

        string failo_pav = "studentai" + to_string(studentu_skaicius[x]) + ".txt";

        ofstream fr(failo_pav);
        fr << left << setw(15) << "Vardas" << setw(15) << "Pavarde";
        for (int i = 0;i < nd_skaicius; i++) {
            fr << setw(5) << "ND" + to_string(i + 1);
        }
        fr << setw(5) << "Egz." << endl;

        for (int i = 0;i < studentu_skaicius[x]; i++) {
            string vardas = "Vardas";
            string pavarde = "Pavarde";
            vardas += to_string(i + 1);
            pavarde += to_string(i + 1);

            fr << left << setw(15) << vardas << setw(15) << pavarde;
            for (int j = 0; j < nd_skaicius + 1; j++) {
                int random_ivertinimas = 1 + (rand() % 10);
                fr << setw(5) << random_ivertinimas;
            }
            fr << endl;
        }

        fr.close();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        double time_taken_in_seconds = duration.count() / 1000000.0;
        cout << "Kiek laiko uztruko sugeneruoti " + to_string(studentu_skaicius[x]) + " studentu faila: "
            << fixed << setprecision(3) << time_taken_in_seconds << " Seconds" << endl;
    }
}

double Galutinis_balas(vector<int> nd_pazymiai, double egz_rezultatas)
{
    double suma = 0;
    for (int i = 0;i < nd_pazymiai.size();i++) {
        suma += nd_pazymiai[i];
    }
    double vidurkis = suma / nd_pazymiai.size();
    double galutinis = 0.4 * vidurkis + 0.6 * egz_rezultatas;

    return galutinis;
}

double Mediana(vector<int> nd_pazymiai, double egz_rezultatas)
{
    double mediana;
    sort(nd_pazymiai.begin(), nd_pazymiai.end());
    if (nd_pazymiai.size() % 2 == 1)
        mediana = nd_pazymiai[nd_pazymiai.size() / 2];
    else
        mediana = (nd_pazymiai[nd_pazymiai.size() / 2 - 1] + nd_pazymiai[nd_pazymiai.size() / 2]) / 2;

    double mediana_galutinis = 0.4 * mediana + 0.6 * egz_rezultatas;
    return mediana_galutinis;
}

void Skaityk_faila(list<info>& studentas, int* pazymiu_sk, int& studentu_skaicius)
{
    auto start = high_resolution_clock::now();
    string line;
    int temp;
    info helper;

    ifstream fd;
    string failo_pavadinimas = "studentai" + to_string(studentu_skaicius) + ".txt";
    fd.open(failo_pavadinimas);

    getline(fd >> ws, line);
    *pazymiu_sk = zodziu_stringe(line) - 3;
    if (fd.is_open())
    {
        vector<int> nd_pazymiai;
        while (fd)
        {   
            fd >> helper.vardas;
            fd >> helper.pavarde;
            for (int i = 0; i < *pazymiu_sk; i++)
            {
                fd >> temp;
                nd_pazymiai.push_back(temp);
            }
            fd >> helper.egz_rezultatas;

            helper.galutinis = Galutinis_balas(nd_pazymiai, helper.egz_rezultatas);
            helper.galutinis_mediana = Mediana(nd_pazymiai, helper.egz_rezultatas);
            nd_pazymiai.clear();
            studentas.push_back(helper);
        }
        studentas.pop_back();
    }
    else
    {
        cout << "Nepavyko atidaryti failo" << endl;
        cout << "Galimai reikia prideti .txt prie pavadinimo kode" << endl;
        exit(1);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    double time_taken_in_seconds = duration.count() / 1000000.0;
    cout << "Failo nuskaitymas su " << studentu_skaicius << " studentu trukme: " << time_taken_in_seconds << " s" << endl;
    fd.close();
}

bool pagalba_rusiavimui(const info& kaire, const info& desine)
{
    return kaire.vardas < desine.vardas;
}

void Rusiuok(list<info>& studentas, int& studentu_skaicius)
{
    auto start = high_resolution_clock::now();
    studentas.sort(pagalba_rusiavimui);


    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    double time_taken_in_seconds = duration.count() / 1000000.0;
    cout << "Duomenu rusiavimo su " << studentu_skaicius << " studentu trukme: " << time_taken_in_seconds << " s" << endl;

}

void Vargseliai_ir_Kietiakai(list<info>& studentas, list<info>& vargseliai, list<info>& kietiakai, int& studentu_skaicius)
{
    auto start = high_resolution_clock::now();
    for (auto i : studentas)
    {
        if (i.galutinis < 5)
        {
            vargseliai.push_back(i);
        }
        else
        {
            kietiakai.push_back(i);
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    double time_taken_in_seconds = duration.count() / 1000000.0;
    cout << "Duomenu skirstymas i vargselius ir kietiakus su " << studentu_skaicius << " studentu trukme: " << time_taken_in_seconds << " s" << endl;

}

void Rasyk_i_faila(list<info>& vargseliai, list<info>& kietiakai, int& studentu_skaicius)
{
    auto start = high_resolution_clock::now();

    string failo_pavadinimas_vargseliai = "rezultatai/" + to_string(studentu_skaicius) + "_vargseliu_rez" + ".txt";
    string failo_pavadinimas_kietiakai = "rezultatai/" + to_string(studentu_skaicius) + "_kietiakiu_rez" + ".txt";


    ofstream frvarg(failo_pavadinimas_vargseliai);
    ofstream frkiet(failo_pavadinimas_kietiakai);


    frvarg << left << setw(20) << "Pavarde" << setw(20) << "Vardas";
    frvarg << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    frvarg << "-------------------------------------------------------------------------------" << endl;

    frkiet << left << setw(20) << "Pavarde" << setw(20) << "Vardas";
    frkiet << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    frkiet << "-------------------------------------------------------------------------------" << endl;
    for (auto i : vargseliai)
    {
        frvarg << fixed << left << setw(20) << i.pavarde << setw(20) << i.vardas;
        frvarg << setw(20) << setprecision(2) << i.galutinis << setw(20) << setprecision(2) << i.galutinis_mediana << endl;
    }
    for (auto i : kietiakai)
    {
        frkiet << fixed << left << setw(20) << i.pavarde << setw(20) << i.vardas;
        frkiet << setw(20) << setprecision(2) << i.galutinis << setw(20) << setprecision(2) << i.galutinis_mediana << endl;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    double time_taken_in_seconds = duration.count() / 1000000.0;
    cout << "Duomenu rasymo i faila su " << studentu_skaicius << " studentu trukme: " << time_taken_in_seconds << " s" << endl;
    cout << endl;
    frvarg.close();
    frkiet.close();
    return;
}

int main()
{
    int pazymiu_sk;
    list<info> studentas, vargseliai, kietiakai;
    int studentu_skaicius = 1000000;

    //Sugeneruok_failus();
    Skaityk_faila(studentas, &pazymiu_sk, studentu_skaicius);
    Rusiuok(studentas, studentu_skaicius);
    Vargseliai_ir_Kietiakai(studentas, vargseliai, kietiakai,studentu_skaicius);
    Rasyk_i_faila(vargseliai, kietiakai, studentu_skaicius);
    studentas.clear();
    vargseliai.clear();
    kietiakai.clear();

    return 0;
}
