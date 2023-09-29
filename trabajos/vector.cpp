#include <iostream>
#include <vector>
#include <string>
//luego hacer un programa donde  ingresen calificaiones y saque el promedio con vectores 

int main()
{
    std::vector <int> vect;

    int num; 
    std::cout << "dime cuantos numero quieres intruducir: ";
    std::cin >> num;

    for (int i=0;i<num;i++){
        int numero;
        std::cout << "dame un numero: ";
        std::cin >> numero;

        vect.push_back(numero);// sirve para poner un tamaño al vector
    }

    for(int i=0; i < vect.size();i++){// vect.size sirve para mostrar de cuanto es el vector 
        std::cout << vect[i] << std::endl;
    }

    for (std::vector<int>::iterator it = vect.begin(); it !=vect.end(); ++it){
        std::cout << *it << std::endl;
    }


    return 0;
}