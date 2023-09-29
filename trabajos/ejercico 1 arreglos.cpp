#include <iostream>


using namespace std;

int main()
{
    int numeros [] = {1,2,3,4,5};// definicion del vector 
    int suma = 0;

    for(int i=0;i<5;i++){// se pone i=0 por que inicia desde el 0
        suma += numeros [i]; // suma += es igual que poner suma = suma + numeros
    }

    cout << "La suma de los numeros del vector es: "<<suma<<endl;

    return 0;
}