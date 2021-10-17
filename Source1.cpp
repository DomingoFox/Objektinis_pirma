
#include "header.h"


unsigned int zodziu_stringe(std::string const& str)
{
    stringstream stream(str);
    return distance(std::istream_iterator<string>(stream), std::istream_iterator<string>());
}

void Skaityk_faila(vector<info>& studentas, int* pazymiu_sk)
{
    string line;
    int studentu = 0;
    int temp;
    try {
        ifstream fd;
        fd.open("studentai10000.txt.txt");

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
        cout << "Duomenys nuskaityti is failo" << endl;
    }
    catch (std::exception& e) {
        cout << "An exception occurred." << endl;
    }
}

bool pagalba_rusiavimui(const info& kaire, const info& desine)
{
    return kaire.vardas < desine.vardas;
}

void Rusiuok(vector<info>& studentas)
{
    sort(studentas.begin(), studentas.end(), pagalba_rusiavimui);
}

void Galutinis_balas(vector<info>& studentas)
{

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
    return;
}

void Mediana(vector<info>& studentas)
{
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
    return;
}

void Rasyk_i_faila(vector<info>& studentas, int pazymiu_sk)
{
    try {
        cout << "Pradedamas duomenu rasymas i faila" << endl;
        ofstream fr("rezultatai.txt");
        fr << left << setw(20) << "Pavarde" << setw(20) << "Vardas";
        fr << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
        fr << "-------------------------------------------------------------------------------" << endl;
        for (int i = 0; i < studentas.size(); i++)
        {
            fr << fixed << left << setw(20) << studentas[i].pavarde << setw(20) << studentas[i].vardas;
            fr << setw(20) << setprecision(2) << studentas[i].galutinis << setw(20) << setprecision(2) << studentas[i].galutinis_mediana << endl;
        }
    }
    catch (std::exception& e) {
        cout << "An exception occurred when writting to file." << endl;
    }
    return;
}
