#include <iostream>

// Definición de la función definida por el usuario doprint ()
void doPrint () //doPrint () es la función llamada en este ejemplo
{
    std::cout << "En doPrint () \n";
}

// Definición de la función main ()
int main ()
{
    std::cout << "inicializando main () \n";
    doPrint (); // Interrumpe main () haciendo una llamda de función a doPrint (). main () es la persona que llama.
    std::cout << "Finalizando main () \n"; // esta sentencia se ejecuta después de que termine doPrint () 
    return 0; 
    /*
    @Autor : Edgar Rodriguez Briseño
    @Fecha : 14/09/2023
    */ 
}