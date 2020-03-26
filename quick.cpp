#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

/* =====================================================================================
Opis funkcji wczytaj_tablice_intow() wczytujacej tablice liczb calkowitych.
Argumenty jakie przyjmuje to: 
- wskaznik na tablice o wartosciach typu calkowitoliczbowego, do ktorej maja zostac
 wpisane liczby
- rozmiar tablicy
Funkcja ta niczego nie zwraca, jest typu void. Sczytuje wartosci(liczby pseudolosowe) zapisane w odpowienim 
pliku .dat" i przypisuje je do odpowiednich komorek tablicy.
====================================================================================== */
void wczytaj_tablice_intow(int* tab, int rozmiar)
{
    int i = 0;
    fstream plik;
    string linia;
    string nazwa = to_string(rozmiar) + ".dat"; // tworzenie odpowiedniej nazwy pliku do otwarcia

    plik.open(nazwa, ios::in);
    
    if(plik.good() == false)
        {
            cout << "Plik nie istnieje" << endl << endl;
            return;
        }

    else
    {
        while(getline(plik,linia))  // dopoki sa linie w pliku
        {
            tab[i] = stoi(linia);   // konwersja ze zmiennej typu string do zmiennej typu int
            i++;
        }   
    }

    plik.close();
}






/* ===================================================================================
Szablon funkcji quick_sort() sortujacej dane wedlug algorytmu sortowania szybkiego.
Argumenty jakie przyjmuje to: 
- wskaznik na tablice o wartosciach zadanego typu, ktora nalezy posortowac
- indeks pierwszego elementu tablicy
- indeks ostatniego elementu tablicy
Funkcja ta niczego nie zwraca, jest typu void, wykonuje jedynie operacje sortowania.
==================================================================================== */
template <typename typ>
void quick_sort(typ* tab, int l, int p)
{
    if(l >= p)      // warunek konca wywolania rekursji
        return;

    typ srodek = tab[(l + p)/2];    // wybranie pivota

    int ind1 = l;
    int ind2 = p;

    while(ind1 <= ind2)
    {
        while(tab[ind1] < srodek)  // wyszukiwanie elementu wiekszego od pivota w lewej czesci tablicy
            ind1++;
        

        while(tab[ind2] > srodek)  // wyszukiwanie elementu mniejszego od pivota w prawej czesci tablicy
            ind2--;
   
 
        if(ind1 <= ind2)      // zamiana znalezionych w powyzszych petlach while komorek tablicy
        {
            swap(tab[ind1],tab[ind2]);
            ind1++;
            ind2--;
        }
    
        else
            break;
     
    }

    if(ind2 > l)       // sortowanie jednej z czesci oryginalnej tablicy podzielonej przez pivota 
        quick_sort(tab,l,ind2);

    if(ind1 < p)       // sortowanie drugiej z czesci oryginalnej tablicy podzielonej przez pivota 
        quick_sort(tab,ind1,p);
}




int main()
{
    int size[5] = {10000, 50000, 100000, 500000, 1000000}; // rozmiar pojedynczej tablicy
    int count_tab = 100;  // ilosc tablic
    double procent[8] = {0, 0.25, 0.5, 0.75, 0.95, 0.99, 0.997, 1}; // poziom posortowania tablicy, 0 - randomowo, 1 - odwrotnie
    int** tab = new int* [count_tab]; 
    double start = 0;
    double stop = 0; 

    // SORTOWANIE TABLIC METODA QUICKSORT  
    // =====================================================================================================================================
    for(int i=0;i<5;i++)    // petla do sortowania po wszystkich rozmiarach tablicy
    {
        for(int j=0;j<count_tab;j++)    // utworzenie tablicy tablic
            tab[j] = new int [size[i]];

        for(int ind=0;ind<8;ind++)  // indeks ind przemieszcza sie po poziomie posortowania oryginalnej tablicy
        {
            for(int j=0;j<count_tab;j++)
                wczytaj_tablice_intow(tab[j],size[i]);

            if(procent[ind] == 0)   // sortowanie tablicy o wartosciach wybranych randomowo
                {
                    start = clock();
                    for(int j=0;j<count_tab;j++)
                        quick_sort(tab[j],0,size[i]-1);
                    stop = clock();

                    cout << "Czas sortowania 100 randomowych tablic " << size[i] << "-elementowych to: " << setprecision(5) << (stop - start)/CLOCKS_PER_SEC << "s" <<  endl;

                }

            else if(procent[ind] == 1)  // sortowanie tablicy juz posortowanej w odwrotnej kolejnosci
            {
                for(int j=0;j<count_tab;j++)
                    {
                        quick_sort(tab[j],0,size[i]-1);
                        reverse(tab[j],tab[j]+size[i]);
                    }
                        

                start = clock();
                for(int j=0;j<count_tab;j++)
                    quick_sort(tab[j],0,size[i]-1);
                stop = clock();

                cout << "Czas sortowania 100 odwrotnie posortowanych tablic " << size[i] << "-elementowych to: " << setprecision(5) << (stop - start)/CLOCKS_PER_SEC << "s" <<  endl;
                cout << endl << endl;
            }

            else        // sortowanie tablicy w zaleznosci od wartosci wspolczynnika posortowania
            {
                for(int j=0;j<count_tab;j++)    // wstepne posortowanie tablicy do odpowiedniego poziomu        
                    quick_sort(tab[j],0,(int)(procent[ind]*size[i])-1);

                start = clock();
                for(int j=0;j<count_tab;j++)
                    quick_sort(tab[j],0,size[i]-1);
                stop = clock();

                cout << "Czas sortowania 100 w " << procent[ind]*100.0 << "% posortowanych tablic " << size[i] << "-elementowych to: " << setprecision(5) << (stop - start)/CLOCKS_PER_SEC << "s" <<  endl;

            }
        }

         
        for(int j=0;j<count_tab;j++)    // usuniecie 100 tablic o zadanym wczesniej rozmiarze
            delete [] tab[j];
    }


    delete [] tab;  // usuniecie tablicy wskaznikow


    return 0;
}