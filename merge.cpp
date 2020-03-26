#include <iostream>
#include <cstdlib>
#include <ctime>
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




/* =====================================================================================
Szablon funkcji merge_sort() sortujacej dane wedlug algorytmu sortowania przez scalanie.
Argumenty jakie przyjmuje to: 
- wskaznik na tablice o wartosciach zadanego typu, ktora nalezy posortowac
- wskaznik na tablice pomocnicza o wartosciach tego samego typu co w sortowanej tablicy
- indeks pierwszego elementu tablicy
- indeks ostatniego elementu tablicy
Funkcja ta niczego nie zwraca, jest typu void, wykonuje jedynie operacje sortowania.
====================================================================================== */
template <typename typ>
void merge_sort(typ* tab, typ* pom, int poczatek, int koniec)
{
    int ind1 = poczatek;
    int srodek = (poczatek + koniec + 1)/2; // wybranie elementu srodkowego
    int ind2 = srodek;
    int i = poczatek;

    if(srodek - poczatek > 1)   // rekurencyjne wywolywanie funkcji sortujacej merge_sort dla lewej czesci podzielonej tablicy
        merge_sort(tab,pom,poczatek,srodek - 1);

   
    
        if(koniec - srodek > 0)  // rekurencyjne wywolywanie funkcji sortujacej merge_sort dla prawej czesci podzielonej tablicy
            merge_sort(tab,pom,srodek,koniec);

        
        
            for(i=poczatek;i<=koniec;i++)   //petla scalajaca posortowane wczesniej elementy ze soba
            {
                if((ind1 == srodek) || (ind2 <= koniec && tab[ind1] > tab[ind2]))
                {
                    pom[i] = tab[ind2];
                    ind2++;
                }

                else
                {
                    pom[i] = tab[ind1];
                    ind1++;
                }
            }

            for(i=poczatek;i<=koniec;i++)   //przepisywanie uporzadkowanych liczb ze zbioru tymczasowego do oryginalnej tablicy
                tab[i] = pom[i];

}
    




/*

int main()
{
    int size = 1000000;
    int count_tab = 100;
    int** tab;

    tab = new int* [count_tab];

    for(int i=0;i<count_tab;i++)
        tab[i] = new int [size];

    srand(time(NULL));

    for(int i=0;i<count_tab;i++)
        for(int j=0;j<size;j++)
            tab[i][j] = rand() % 1000000;

    double start = clock();

    for(int i=0;i<count_tab;i++)
        merge_sort(0,size-1);

    double stop = clock();

    cout << "Czas sortowania " << count_tab << " tablic to: " << setprecision(5) << (stop - start)/CLOCKS_PER_SEC << endl << endl;


    for(int i=0;i<count_tab;i++)
        delete [] tab[i];

    delete [] tab;








    /*
    srand(time(NULL));

    for(int i=0;i<n;i++)
        tab[i] = rand() % 100000;
    
    //for(int i=0;i<n;i++)
      //  cout << tab[i] << endl;
     

    cout << endl << endl;
     double start = clock();

    merge_sort(0,n-1);
    double stop = clock();

    cout << "czas:  " << setprecision(5) << (stop-start)/CLOCKS_PER_SEC << endl;


    //for(int i=0;i<n;i++)
      //  cout << tab[i] << endl;

    return 0;
   
} */



int main()
{
    int size[5] = {10000, 50000, 100000, 500000, 1000000}; // rozmiar pojedynczej tablicy
    int count_tab = 100;  // ilosc tablic
    double procent[8] = {0, 0.25, 0.5, 0.75, 0.95, 0.99, 0.997, 1}; // poziom posortowania tablicy, 0 - randomowo, 1 - odwrotnie
    int** tab = new int* [count_tab]; 
    int* pom;// = new int [count_tab];
    double start = 0;
    double stop = 0;
    



    // SORTOWANIE TABLIC METODA MERGESORT  
    // =====================================================================================================================================
    for(int i=0;i<5;i++)    // petla do sortowania po wszystkich rozmiarach tablicy
    {
        for(int j=0;j<count_tab;j++)    // utworzenie tablicy tablic
            tab[j] = new int [size[i]];

        //for(int j=0;j<count_tab;j++)    
            pom = new int [size[i]];    // utworzenie pomocniczej tablicy  

        for(int ind=0;ind<8;ind++)  // indeks ind przemieszcza sie po poziomie posortowania oryginalnej tablicy
        {
            for(int j=0;j<count_tab;j++)
                wczytaj_tablice_intow(tab[j],size[i]);

            if(procent[ind] == 0)   // sortowanie tablicy z liczbami pseudolosowymi
                {
                    start = clock();
                    for(int j=0;j<count_tab;j++)
                        merge_sort(tab[j],pom,0,size[i]-1);
                    stop = clock();

                    cout << "Czas sortowania 100 randomowych tablic " << size[i] << "-elementowych to: " << setprecision(5) << (stop - start)/CLOCKS_PER_SEC << "s" <<  endl;

                }

            else if(procent[ind] == 1)  // sortowanie tablicy posortowanej odwrotnie
            {
                for(int j=0;j<count_tab;j++)
                    {
                        merge_sort(tab[j],pom,0,size[i]-1);
                        reverse(tab[j],tab[j]+size[i]);
                    }
                        

                start = clock();

                for(int j=0;j<count_tab;j++)
                    merge_sort(tab[j],pom,0,(int)(procent[ind]*size[i])-1);
                stop = clock();

                cout << "Czas sortowania 100 odwrotnie posortowanych tablic " << size[i] << "-elementowych to: " << setprecision(5) << (stop - start)/CLOCKS_PER_SEC << "s" <<  endl;
                cout << endl << endl;
            }

            else    // sortowanie tablicy o odpowiednim stopniu posortowania
            {
                for(int j=0;j<count_tab;j++)    // wstepne posortowanie tablicy do odpowiedniego poziomu       
                    merge_sort(tab[j],pom,0,(int)(procent[ind]*size[i])-1);

                start = clock();
                for(int j=0;j<count_tab;j++)
                    merge_sort(tab[j],pom,0,size[i]-1);
                stop = clock();

                cout << "Czas sortowania 100 " << procent[ind]*100.0 << "% posortowanych tablic " << size[i] << "-elementowych to: " << setprecision(5) << (stop - start)/CLOCKS_PER_SEC << "s" <<  endl;

            }
        }


    for(int j=0;j<count_tab;j++)    // usuniecie 100 tablic o zadanym wczesniej rozmiarze
            delete [] tab[j];

    //for(int j=0;j<count_tab;j++)    // usuniecie 100 pomocniczych tablic o zadanym wczesniej rozmiarze
            //delete [] pom[j];

        



    }

    
    delete [] tab;
    delete [] pom;

    return 0;
}