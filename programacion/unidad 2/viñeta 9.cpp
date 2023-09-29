#include <iostream>

void doB()
{
    std::cout << "En doB () \n";
}

void doA()
{
    std::cout << "Inicializando doA () \n";
    doB(); // aqui llama a void doB 
    std::cout << "Finalizando doA () \n";
}

//Definición de la función main ()
int main()
{
    std::cout << "Iniciando main () \n";
    doA();
    std::cout << "Finalizando main () \n";
    return 0;
    /*
    @Autor : Edgar Rodriguez Briseño
    @Fecha : 14/09/2023
    */ 
}