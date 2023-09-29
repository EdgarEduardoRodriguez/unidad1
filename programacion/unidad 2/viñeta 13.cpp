#include <iostream>

void doB()
{
    std::cout << "En doB()\n";
}

void doA()
{
    std::cout <<"enn doA()\n";
    doB();
}

// Definicion de la función main()
int main()
{
    std::cout << "Inicializando mian()\n";
    doA();
    doB();
    std::cout << "Finalizando main()\n";
    return 0;
    /*
    @Autor : Edgar Rodriguez Briseño
    @Fecha : 18/09/2023
    */ 
}