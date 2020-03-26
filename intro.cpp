#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

// Prototypy uzywanych funkcji:

template <typename typ>
void intro_sort(typ* tab, int N, int M);    // funkcja sortujaca podana tablice

template <typename typ>
int podziel(typ* tab, int l, int p);        // funkcja dzielaca tablice na pol

template <typename typ>
void zmien_elem(typ* tab, int &l, int &p);  // funkcja zamieniajaca poszczegolne elementy tablicy ze soba

template <typename typ>
void sort_kopcowe(typ* tab, int N);         // funkcja sortujaca tablice przez kopcowanie

template <typename typ>                     // funkcja wykonujaca operacje na kopcu danych
void kopiec(typ* tab, int i, int N);

template <typename typ>
void sort_wstaw(typ* tab, int N);           // funkcja sortujaca tablice przez wstawianie



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
Szablon funkcji introspekt_sort() sortujacej dane wedlug algorytmu sortowania introspektywnego.
Argumenty jakie przyjmuje to: 
- wskaznik na tablice o wartosciach zadanego typu, ktora nalezy posortowac
- liczba elementow znajdujacych sie w podanej tablicy
Funkcja ta niczego nie zwraca, jest typu void, wykonuje jedynie operacje sortowania.
==================================================================================== */
template <typename typ>
void introspekt_sort(typ* tab, int N)
{
    int M = floor(2*log(N)/log(2));    // max glebokosc wywolan rekurencyjnych
    intro_sort(tab,N,M);
    sort_wstaw(tab,N);
}



/* ===================================================================================
Szablon funkcji intro_sort() sortujacej dane wedlug algorytmu sortowania introspektywnego.
Argumenty jakie przyjmuje to: 
- wskaznik na tablice o wartosciach zadanego typu, ktora nalezy posortowac
- liczba elementow znajdujacych sie w podanej tablicy
- wartosc maxymalnej glebokosci wywolan rekurencyjnych
Funkcja ta niczego nie zwraca, jest typu void, wykonuje jedynie operacje sortowania 
przez kopcowanie lub wywoluje siebie sama rekurencyjnie.
==================================================================================== */
template <typename typ>
void intro_sort(typ* tab, int N, int M)
{
    if(M <= 0)
    {
        sort_kopcowe(tab,N);
        return;
    }

    int i = podziel(tab,0,N);

    if(i > 9)       // 9 - liczba podzbiorow oryginalnej tablicy po podziale przez funkcje "podziel"
        intro_sort(tab,i,M-1);

    if(N-1-i > 9)
        intro_sort(tab+i+1,N-i-1,M-1);

}



/* ===================================================================================
Szablon funkcji podziel() dzielaca tablice na dwie czesci. W lewej jej czesci sa 
gromadzone wartosci mniejsze od wartosci elementu srodkowego, a w prawej wieksze.
Argumenty jakie przyjmuje to: 
- wskaznik na tablice o wartosciach zadanego typu, ktora nalezy posortowac
- indeks pierwszego elementu tablicy
- indeks ostatniego elementu tablicy
Funkcja ta jest typu int, zwraca indeks zamienionego elementu tablicy.
==================================================================================== */
template <typename typ>
int podziel(typ* tab, int l, int p)
{
    int ind1 = 0;
    int ind2 = 0;
    
    if(p >= 3)
        swap(tab[l],tab[p]);

    for(ind1=l,ind2=p-2; ;)
    {
        for(; tab[ind1]<tab[p-1];ind1++);

        for(; ind2>=l && tab[ind2]>tab[p-1];ind2--);

        if(ind2 > ind21)
            swap(tab[ind1++],tab[ind2--]);
            
        else break;

    }

    swap(tab[ind1],tab[p-1]);
    return ind1;
}



/* ===================================================================================
Szablon funkcji zmien_elem() zamieniajacej wskazane dwa elementy.
Argumenty jakie przyjmuje to: 
- wskaznik na tablice o wartosciach zadanego typu, ktora nalezy posortowac
- referencje do indeksu pierwszego elementu tablicy
- referencje do indeksu ostatniego elementu tablicy
Funkcja ta jest typu void.
==================================================================================== */
template <typename typ>
void zmien_elem(typ* tab, int &l, int &p)
{
    if(tab[++l-1] > tab[--p])
        swap(tab[l-1],tab[p]);

     if(tab[l-1] > tab[p/2])
        swap(tab[l-1],tab[p/2]);

     if(tab[p/2] > tab[p])
        swap(tab[p/2],tab[p-1]);
}



/* ===================================================================================
Szablon funkcji sort_kopcowe() sortujacej tablice wedlug algorytmu sortowania 
przez kopcowanie.
Argumenty jakie przyjmuje to: 
- wskaznik na tablice o wartosciach zadanego typu, ktora nalezy posortowac
- rozmiar tablicy
Funkcja ta jest typu void.
==================================================================================== */
template <typename typ>
void sort_kopcowe(typ* tab, int N)
{
    int i = 0;

    for(i=N/2;i>0;i--)
        kopiec(tab-1,i,N);
    
    for(i=N-1;i>0;i--)
    {
        swap(tab[0],tab[i]);
        kopiec(tab-1,1,i);
    }
}


/* ===================================================================================
Szablon funkcji kopiec() wykonujacej operacje na kopcu(np rozbieranie kopca), ktory jest potrzebny do 
funkcji sortujacej sort_kopcowe().
Argumenty jakie przyjmuje to: 
- wskaznik na tablice o wartosciach zadanego typu, ktora nalezy posortowac
- rozmiar tablicy
- dodatkowy indeks
Funkcja ta jest typu void.
==================================================================================== */
template <typename typ>
void kopiec(typ* tab, int i, int N)
{
    int j = 0;

    while(i <= N/2)   
    {
        j=2*i;
        if(j+1 <= N && tab[j+1] > tab[j])
            j++;
        
        if(tab[i] < tab[j])
            swap(tab[i],tab[j]);
        else break;
        i = j;
    }
}


/* ===================================================================================
Szablon funkcji sort_wstaw() sortujacej tablice wedlug algorytmu sortowania 
przez wstawianie.
Argumenty jakie przyjmuje to: 
- wskaznik na tablice o wartosciach zadanego typu, ktora nalezy posortowac
- rozmiar tablicy
Funkcja ta jest typu void.
==================================================================================== */
template <typename typ>
void sort_wstaw(typ* tab, int N)
{
    int i = 0;
    int j = 0;
    typ temp;

    for(i=1;i<N;i++)
    {
        temp = tab[i];

        for(j=i;j>0 && temp<tab[j-1];j--)
            tab[j] = tab[j-1];
        
        tab[j] = temp;
    }
}






int main()
{
    int size[5] = {10000, 50000, 100000, 500000, 1000000}; // rozmiar pojedynczej tablicy
    int count_tab = 100;  // ilosc tablic
    double procent[8] = {0, 0.25, 0.5, 0.75, 0.95, 0.99, 0.997, 1}; // poziom posortowania tablicy, 0 - randomowo, 1 - odwrotnie
    int** tab = new int* [count_tab]; 
    double start = 0;
    double stop = 0;
    



    // SORTOWANIE TABLIC SORTOWANIEM INTROSPEKTYWNYM 
    // =====================================================================================================================================
    for(int i=0;i<5;i++)    // petla do sortowania po wszystkich rozmiarach tablicy
    {
        for(int j=0;j<count_tab;j++)    // utworzenie tablicy tablic
            tab[j] = new int [size[i]];

        for(int ind=0;ind<8;ind++)  // indeks ind przemieszcza sie po poziomie posortowania oryginalnej tablicy
        {
            for(int j=0;j<count_tab;j++)
                wczytaj_tablice_intow(tab[j],size[i]);

            if(procent[ind] == 0)   // sortowanie tablicy z liczbami pseudolosowymi
                {
                    start = clock();
                    for(int j=0;j<count_tab;j++)
                        introspekt_sort(tab[j],size[i]);
                    stop = clock();

                    cout << "Czas sortowania 100 randomowych tablic " << size[i] << "-elementowych to: " << setprecision(5) << (stop - start)/CLOCKS_PER_SEC << "s" <<  endl;

                }

            else if(procent[ind] == 1)  // sortowanie tablicy posortowanej odwrotnie
            {
                for(int j=0;j<count_tab;j++)
                    {
                        introspekt_sort(tab[j],size[i]);
                        reverse(tab[j],tab[j]+size[i]);
                    }

                start = clock();
                for(int j=0;j<count_tab;j++)
                    introspekt_sort(tab[j],size[i]);
                stop = clock();

                cout << "Czas sortowania 100 odwrotnie posortowanych tablic " << size[i] << "-elementowych to: " << setprecision(5) << (stop - start)/CLOCKS_PER_SEC << "s" <<  endl;
                cout << endl << endl;
            }

            else    // sortowanie tablicy o odpowiednim stopniu posortowania
            {
                for(int j=0;j<count_tab;j++)       
                    introspekt_sort(tab[j],(int)(procent[ind]*size[i]));

                start = clock();
                for(int j=0;j<count_tab;j++)
                    introspekt_sort(tab[j],size[i]);
                stop = clock();

                cout << "Czas sortowania 100 " << procent[ind]*100.0 << "% posortowanych tablic " << size[i] << "-elementowych to: " << setprecision(5) << (stop - start)/CLOCKS_PER_SEC << "s" <<  endl;

            }
        }

    for(int j=0;j<count_tab;j++)
            delete [] tab[j];
    }

    
    delete [] tab;

    return 0;
}



