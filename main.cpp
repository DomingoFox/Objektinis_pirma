
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <fstream>
#include <string>
#include <sstream>

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

struct info
{
    string vardas, pavarde;
    double egz_rezultatas, galutinis, mediana, galutinis_mediana;
    vector<double> nd_rezultatai;
};

void Skaityk_faila(vector<info>& studentas, double& n)
{   
    string filename_pattern = "kursiokai.txt";
    string line;
    int number_of_words;

    ifstream fd(filename_pattern); 

    getline(fd, line);
   
    for (int i = 0; i < line.length(); i++)
    {   
        int temp = 0;
        int count = 0;
        while (line[i]) {
            if (line[i] == ' ' || line[i] == '\n' || line[i] == '\t') {
                temp = 0;
            }
            else if (temp == 0) {
                temp = 1;
                count++;
            }
            i++;
        }
        number_of_words = count - 2;
    }
    int help = number_of_words;
    int i = 0;
    string temp;
    int count_lines = 0;
    while (!fd.eof())
    {   
        count_lines++;
        studentas.resize(studentas.size() + 1);
        fd >> studentas[i].pavarde >> studentas[i].vardas;
        for (int j = 0;j < help ;j++)
        {
            fd >> temp;
            studentas[i].nd_rezultatai.push_back(stoi(temp));
        }
        i++;
    }

    n = count_lines;
}

void Skaityk(vector<info> &studentas, double &n)
{
    double temp;
    
    cout << "Iveskite studentu skaiciu: " << endl;
    cin >> n;
    
    while (cin.fail() || n < 0 || (int) n != n)
    {   
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Neteisinga ivestis!" << endl;
        cout << "Iveskite studentu skaiciu: " << endl;
        cin >> n;
    }
    
    if (n == 0)
    {
        cout << "Nera studentu duomenu" << endl;
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {   
        studentas.push_back(info());
        cout << "Iveskite " << i + 1 << "-ojo studento varda ir pavarde" << endl;
        cin >> studentas[i].vardas >> studentas[i].pavarde;
        cin.clear();
        cin.ignore(10000, '\n');
        string atsitiktinai;
        cout << "Ar balai uz namu darbus ir egzamina sitam studentui turetu buti generuojami atsitiktinai? y(yes)/n(no)" << endl;
        cin >> atsitiktinai;
        if (atsitiktinai == "y" || atsitiktinai == "yes" || atsitiktinai == "Y")
        {
            int nd_ivertinimu_sk = 5;
            int min = 1;
            int max = 10;
            cout << "Sugeneruoti ivertinimai: ND:";
            for (int j = 0; j < nd_ivertinimu_sk; j++)
            {
                int random_ivertinimas = min + (rand() % (max - min + 1));
                cout << random_ivertinimas << " ";
                studentas[i].nd_rezultatai.push_back(random_ivertinimas);
            }
            int random_ivertinimas = min + (rand() % (max - min + 1));
            studentas[i].egz_rezultatas = random_ivertinimas;
            cout << "egzamino: " << random_ivertinimas << endl;
            continue;
        }
        

        cout << "Iveskite studento ivertinimus (neteisinga ivestis uzbaigia procesa): " << endl;
        while (cin >> temp)
        {   
            if (temp < 0 || temp>10 || cin.fail())
                break;
            studentas[i].nd_rezultatai.push_back(temp);
        }
        cin.clear();
        cin.ignore(10000, '\n');


        cout << "Iveskite " << i + 1 << "-ojo studento egzamino rezultata" << endl;
        cin >> studentas[i].egz_rezultatas;
        while (cin.fail() || studentas[i].egz_rezultatas < 0 || studentas[i].egz_rezultatas>10)
        {   
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Neteisinga ivestis, iveskite egzamino rezultata dar karta: " << endl;
            cin >> studentas[i].egz_rezultatas;
        }
    }
    return;
}

void Galutinis_balas(vector<info> &studentas, double &n)
{   
    
    for (int i = 0; i < n; i++)
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
    return;
}

void Mediana(vector<info> &studentas, double &n)
{   
    for (int i = 0; i < n; i++)
    {
        sort(studentas[i].nd_rezultatai.begin(), studentas[i].nd_rezultatai.end());
    }
    
    for (int i = 0; i < n; i++)
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
    return;
}

void Rasyk(vector<info> &studentas, double &n)
{   
    cout << left << setw(20) << "Pavarde" << setw(20) << "Vardas";
    cout << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << fixed << left << setw(20) << studentas[i].pavarde << setw(20) << studentas[i].vardas;
        cout << setw(20) << setprecision(2) << studentas[i].galutinis << setw(20) << setprecision(2) << studentas[i].galutinis_mediana << endl;
    } 
    return;
}


int main()
{
    double n;
    vector<info> studentas;
    
    Skaityk_faila(studentas, n);
    //Skaityk(studentas, n);
    Galutinis_balas(studentas, n);
    Mediana(studentas, n);
    Rasyk(studentas, n);

    return 0;
}
