
#include <iomanip>
#include <iostream>

using namespace std;

struct info
{
    string vardas, pavarde;
    double nd_rezultatai[101], egz_rezultatas, galutinis, mediana;
};

void Skaityk(info studentas[101], int &n, int &namu_darbu_sk)
{
    cout << "Iveskite studentu skaiciu: " <<endl;
    cin >> n;

    cout << "Kiek namu darbu ivertinimu turejo studentai?" << endl;
    cin >> namu_darbu_sk;
    for(int i=0; i<n ; i++)
    {
        cout << "Iveskite " << i+1 << "-ojo studento varda ir pavarde" << endl;
        cin >> studentas[i].vardas >> studentas[i].pavarde;

        cout << "Iveskite studento ivertinimus: " <<endl;
        for(int j=0; j<namu_darbu_sk; j++)
        {
            cin >> studentas[i].nd_rezultatai[j];
        }

        cout << "Iveskite " << i+1 << "-ojo studento egzamino rezultata" << endl;
        cin >> studentas[i].egz_rezultatas;
    }

    return;
}

void Galutinis_balas(info studentas[101], int &n, int &namu_darbu_sk)
{
    for(int i=0; i<n; i++)
    {
        double nd_suma = 0;
        for(int j=0; j<namu_darbu_sk; j++)
        {
            nd_suma += studentas[i].nd_rezultatai[j];
        }
        double vidurkis = nd_suma/namu_darbu_sk;
        studentas[i].galutinis = 0.4 * vidurkis + 0.6 * studentas[i].egz_rezultatas;
    }

    return;
}

void Mediana(info studentas[101], int &n, int &namu_darbu_sk)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<namu_darbu_sk; j++)
        {
            for(int z=0; z<namu_darbu_sk; z++)
            {
                if(studentas[i].nd_rezultatai[j] > studentas[i].nd_rezultatai[z])
                {
                    swap(studentas[i].nd_rezultatai[j], studentas[i].nd_rezultatai[z]);
                }
            }
        }
    }
    for(int i=0; i<n; i++)
    {
        if(namu_darbu_sk % 2 == 1)
            studentas[i].mediana = studentas[i].nd_rezultatai[namu_darbu_sk/2];
        else
            studentas[i].mediana = (studentas[i].nd_rezultatai[namu_darbu_sk/2-1] + studentas[i].nd_rezultatai[namu_darbu_sk/2])/2;
    }
}

void Rasyk(info studentas[101], int &n)
{
    string isvedimas;
    cout<<"Ar isvesti vidurki(v) ar mediana(m)?"<<endl;
    cin>>isvedimas;
    if(isvedimas == "v" || isvedimas == "vidurkis" || isvedimas == "vidurki")
    {
        cout << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)/Galutinis (Med.)" <<endl;
        cout << "-------------------------------------------------------------" <<endl;
        for(int i=0; i<n; i++)
        {
            cout << fixed << left << setw(20) << studentas[i].pavarde << setw(20) << studentas[i].vardas << setw(20) << setprecision(2) << studentas[i].galutinis <<endl;
        }
    }
    else
    {
        cout << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)/Galutinis (Med.)" <<endl;
        cout << "-------------------------------------------------------------" <<endl;
        for(int i=0; i<n; i++)
        {
            cout << fixed << left << setw(20) << studentas[i].pavarde << setw(20) << studentas[i].vardas << setw(20) << setprecision(2) << studentas[i].mediana <<endl;
        }
    }

    return;
}


int main()
{
    int n, namu_darbu_sk;
    info studentas[101];

    Skaityk(studentas,n,namu_darbu_sk);
    Galutinis_balas(studentas,n,namu_darbu_sk);
    Mediana(studentas,n,namu_darbu_sk);
    Rasyk(studentas,n);

    return 0;
}

