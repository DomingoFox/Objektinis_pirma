
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>

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
    return distance(std::istream_iterator<string>(stream), std::istream_iterator<string>());
}

void Sugeneruok_failus()
{   
    int nd_skaicius = 5;
    const int failu_kiekis = 5;
    int studentu_skaicius[failu_kiekis] = {1000, 10000, 100000, 1000000, 10000000};

    for(int x = 0; x<failu_kiekis ;x++){
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
            vardas += to_string(i+1);
            pavarde += to_string(i+1);
        
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

void Skaityk_faila(vector<info>& studentas, int* pazymiu_sk, int &studentu_skaicius)
{   
    auto start = high_resolution_clock::now();
    string line;
    int studentu = 0;
    int temp;

    ifstream fd;
    string failo_pavadinimas = "studentai" + to_string(studentu_skaicius) + ".txt";
    fd.open(failo_pavadinimas);

    getline(fd >> ws, line);
    *pazymiu_sk = zodziu_stringe(line) - 3;
    cout << fd.is_open() << endl;
    if (fd.is_open())
    {
        while (true)
        {

            studentas.resize(studentas.size() + 1);
            fd >> studentas.at(studentu).vardas;
            if (fd.eof())
            {
                studentas.pop_back();
                break;
            }

            fd >> studentas.at(studentu).pavarde;
            for (int i = 0; i < *pazymiu_sk; i++)
            {
                fd >> temp;
                studentas.at(studentu).nd_rezultatai.push_back(temp);
            }
            fd >> studentas.at(studentu).egz_rezultatas;
            studentu++;
        }
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

void Rusiuok(vector<info>& studentas, int &studentu_skaicius)
{   
    auto start = high_resolution_clock::now();
    sort(studentas.begin(), studentas.end(), pagalba_rusiavimui);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    double time_taken_in_seconds = duration.count() / 1000000.0;
    cout << "Duomenu rusiavimo su " << studentu_skaicius << " studentu trukme: " << time_taken_in_seconds << " s" << endl;

}

void Galutinis_balas(vector<info>& studentas, int &studentu_skaicius)
{
    auto start = high_resolution_clock::now();
    for (int i = 0; i < studentas.size(); i++)
    {
        double nd_suma = 0;
        for (int j = 0; j < studentas[i].nd_rezultatai.size(); j++)
        {
            nd_suma += studentas[i].nd_rezultatai[j];
        }
        if (studentas[i].nd_rezultatai.size() == 0)
        {
            studentas[i].galutinis = 0.6 * studentas[i].egz_rezultatas;
        }
        else
        {
            double vidurkis = nd_suma / studentas[i].nd_rezultatai.size();
            studentas[i].galutinis = 0.4 * vidurkis + 0.6 * studentas[i].egz_rezultatas;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    double time_taken_in_seconds = duration.count() / 1000000.0;
    cout << "Galutinio balo apskaiciavimas su " << studentu_skaicius << " studentu trukme: " << time_taken_in_seconds << " s" << endl;

    return;
}

void Mediana(vector<info>& studentas, int &studentu_skaicius)
{   
    auto start = high_resolution_clock::now();
    for (int i = 0; i < studentas.size();i++)
        sort(studentas[i].nd_rezultatai.begin(), studentas[i].nd_rezultatai.end());

    for (int i = 0; i < studentas.size(); i++)
    {
        int ilgis = studentas[i].nd_rezultatai.size();

        if (ilgis == 0)
        {
            studentas[i].galutinis_mediana = 0.6 * studentas[i].egz_rezultatas;
        }
        else
        {
            if (studentas[i].nd_rezultatai.size() % 2 == 1)
                studentas[i].mediana = studentas[i].nd_rezultatai[ilgis / 2];
            else
                studentas[i].mediana = (studentas[i].nd_rezultatai[ilgis / 2 - 1] + studentas[i].nd_rezultatai[ilgis / 2]) / 2;
            studentas[i].galutinis_mediana = 0.4 * studentas[i].mediana + 0.6 * studentas[i].egz_rezultatas;
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    double time_taken_in_seconds = duration.count() / 1000000.0;
    cout << "Medianos apskaiciavimas su " << studentu_skaicius << " studentu trukme: " << time_taken_in_seconds << " s" << endl;
    return;
}

void vargsiukai_kietiakai(vector<info>& studentas, int pazymiu_sk, int& studentu_skaicius, vector<info>& vargsiukai, vector<info>& kietiakai)
{
    auto start = high_resolution_clock::now();
    for (int i = 0; i < studentas.size(); i++)
    {
        if (studentas[i].galutinis < 5)
        {
            vargsiukai.push_back(studentas[i]);
        }
        else
        {
            kietiakai.push_back(studentas[i]);
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    double time_taken_in_seconds = duration.count() / 1000000.0;
    cout << "Vargsiuku ir kietiaku rasymas i dvieju tipo konteineriu su " << studentu_skaicius << " studentu, trukme: " << time_taken_in_seconds << " s" << endl;
}

void Rasyk_i_faila(vector<info>& studentas, int pazymiu_sk, int &studentu_skaicius, vector<info>& vargsiukai, vector<info>& kietiakai)
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
 
    for (int i = 0; i < vargsiukai.size(); i++)
    {
        frvarg << fixed << left << setw(20) << vargsiukai[i].pavarde << setw(20) << vargsiukai[i].vardas;
        frvarg << setw(20) << setprecision(2) << vargsiukai[i].galutinis << setw(20) << setprecision(2) << vargsiukai[i].galutinis_mediana << endl;
    }

    for (int i = 0; i < kietiakai.size(); i++)
    {
        frkiet << fixed << left << setw(20) << kietiakai[i].pavarde << setw(20) << kietiakai[i].vardas;
        frkiet << setw(20) << setprecision(2) << kietiakai[i].galutinis << setw(20) << setprecision(2) << kietiakai[i].galutinis_mediana << endl;
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
    vector<info> studentas;
    vector<info> vargsiukai;
    vector<info> kietiakai;
    int studentu_skaicius = 1000000;

    //Sugeneruok_failus();
    Skaityk_faila(studentas, &pazymiu_sk,studentu_skaicius);
    Galutinis_balas(studentas, studentu_skaicius);
    Mediana(studentas,studentu_skaicius);
    Rusiuok(studentas,studentu_skaicius);
    vargsiukai_kietiakai(studentas, pazymiu_sk, studentu_skaicius, vargsiukai, kietiakai);
    Rasyk_i_faila(studentas, pazymiu_sk,studentu_skaicius,vargsiukai,kietiakai);

    return 0;
}
