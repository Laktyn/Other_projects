#include <iostream>
#include <chrono>
using namespace std;

void createMatrix(int number, int partitions, long long int matrix[][500]){

    //Ustalamy wartosci brzegowe
    for(long long int i = 0; i < number; i++){
    matrix[i][0] = 1;
    }
    for(long long int i = 1; i < partitions; i++){
    matrix[i][i] = 1;
    }

    //Kolejno zapelniamy komorki macierzy
    long long int sum;
    for(int numb_i = 2; numb_i < number; numb_i++){
    for(int part_i = 1; part_i < partitions && part_i < numb_i; part_i++){ //iterujemy po number i partitions

        sum = 0;
        for(int i = 0; i <= part_i && i <= numb_i - part_i; i++){   //ta petla to kluczowa czesc calego programu
            sum += matrix[numb_i - part_i - 1][i];
        }
        matrix[numb_i][part_i] = sum;
    }}
}
int main(){

//INPUT
cout << "Jesli interesuje cie liczba zapisow liczby k jako sumy n niezerowych skladnikow, to wpisz \"single\". " ;
cout << "Jesli interesuje cie liczba wszystkich zapisow liczby k jako sumy niezerowych skladnikow, to wpisz \"total\"." << endl << endl;
int theNumber = 0;
int thePartitions = 0;
string input;
cout << "Funkcja programu: ";
cin >> input;

if(input == "single"){
    cout << "k = ";
    cin >> theNumber;

    if(theNumber > 500 || theNumber < 1){
        cout << "Liczba spoza zakresu." << endl;
        system("pause");
        return 0;
    }   
    cout << "n = ";
    cin >> thePartitions;
    if(thePartitions < 1){
        cout << "Liczba spoza zakresu." << endl;
        system("pause");
        return 0;
    }
    if(thePartitions > theNumber){
        cout << "Istnieje 0 takich zapisow." << endl;
        system("pause");
        return 0;
    }
}
else if(input == "total"){
    cout << "k = ";
    cin >> theNumber;
    if(theNumber > 450 || theNumber<1){
        cout << "Liczba spoza zakresu." << endl;
        system("pause");
        return 0;
    }
    thePartitions = theNumber;   
}
else{
    cout << endl << "Nieznana komenda." << endl;
    system("pause");
    return 0;
}


//CALCULATIONS - MATRIX FILLING
    auto start = chrono::steady_clock::now();
long long int theMatrix[theNumber][500] = {};
for(long long int i = 0; i < theNumber; i++){
    theMatrix[i][0] = 1; //dajemy jedynki dla zapisu dowolnej liczby jako sumy 1 skladnika
}
for(long long int i = 1; i < thePartitions; i++){
    theMatrix[i][i] = 1; //dajemy jedynki dla zapisu liczby k jako sumy k skladnikow
    }

createMatrix(theNumber, thePartitions, theMatrix);

//RESPONSE
cout << endl;
if(input == "single"){
    cout << endl << "Istnieje " << theMatrix[theNumber - 1][thePartitions - 1] << " takich zapisow." << endl;
}
if(input == "total"){
    long long int result = 0;
    for(int i = 0; i < theNumber; i++){
        result += theMatrix[theNumber - 1][i];
    }
    cout << "Liczbe " << theNumber << " mozna zapisac na " << result << " roznych sposobow." << endl;
}
    auto end = chrono::steady_clock::now();

cout << "Obliczenia zajely " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " mikrosekund." << endl;

cout << endl;
system("pause");
return 0;
}