#include <iostream>

void doPrint ()
{
    std::cout << "En doPrint () \n";
}


// Definicion de la funcion main ()
int main (){
    std::cout << "Inicializando main () \n";
    doPrint (); // doPrint () llamado por primera vez
    doPrint (); // doPrint () llamado por segunda vez
    std::cout << "Finalizando main () \n";

    return 0;
    /*
    @Autor : Edgar Rodriguez Briseño
    @Fecha : 14/09/2023
    */ 
}