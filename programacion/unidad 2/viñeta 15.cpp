#include <iostream>

int getValueFromUser()
{
    std::cout << "Ingrese un entero: \n";
    int input{};
    std::cin >> input;
    return input; // Devolvemos el valor ingresado por el usuario
}

int main()
{
    int num = getValueFromUser(); // Llamamos a la función y guardamos su resultado en 'num'
    std::cout << num << " duplicado es: " << num * 2 << '\n';
    return 0;
    /*
    @Autor : Edgar Rodriguez Briseño
    @Fecha : 18/09/2023
    */ 
}