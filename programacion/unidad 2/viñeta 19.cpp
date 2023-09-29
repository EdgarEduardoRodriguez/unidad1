#include <iostream>

int getValueFromUser()  // esta función ahora devuelve un valor entero
{
    std::cout << "Ingrese un entero: " << std::endl;
    int input{};
    std::cin >> input; 

    return input; // devuelve el valor que el usuario ingresó
}

int main()
{
    int num = getValueFromUser(); //inicializa num con el valor de retorno de getValueFromUser ()
    std::cout << num << " duplicado es: "<< num * 2 << '\n';
    return 0;
    /*
    @Autor : Edgar Rodriguez Briseño
    @Fecha : 18/09/2023
    */ 
}