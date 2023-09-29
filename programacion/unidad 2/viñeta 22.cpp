#include <iostream>

//void significa que la función no devuelve un valor a la persona que llama
void returnNada ()
{
    std::cout << "Hola" <<'\n';
    //Esta funcion no devuelve un valor, por lo que no se necesita una declaracion de devolución
} 

int main ()
{
    returnNada (); // bien: se llama a la funcion returnNdad (), no se devuelve ningún valor 
    //std::cout << returnNada (); error: esta línea no se compilará. deberá comentarlo para continuar
    return 0;
    /*
    @Autor : Edgar Rodriguez Briseño
    @Fecha : 18/09/2023
    */ 
}