#include <iostream>

int main()
{
    //obtener un valor del usuario
    std::cout << "Ingrese un entero\n";
    int num{};
    std::cin >> num;

    //Imprime el valor duplicado
    std::cout << num << " duplicado es: " << num * 2 << '\n';

    return 0;
    /*
    @Autor : Edgar Rodriguez Briseño
    @Fecha : 18/09/2023
    */ 
}