#include <iostream>

using namespace std;

int main()
{
    int numeros [] {1,2,3,4,5};//definicion del vector 
    int mult = 1;// se tiene que dar valor en 1 si esta multiplicando 
    for (int i=0;i<5;i++){
        mult *= numeros [i]; 
    }

    cout<<"La multiplicacion de los numeros del vector es: " <<mult<<endl;

    return 0;
}