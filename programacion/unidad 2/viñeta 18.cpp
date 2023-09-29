#include <iostream>

//int es el tipo de retorno 
//un tipo de retorno de int significa que la función devilverá algún valor entero a la persona que llama (el valor espesifico)
int returnFive()
{
    //la declaración de retirno indica el valor específico que se devolverá 
    return 5; //devuelve el valor específico a la persona que llama
}

int main()
{
    std::cout << returnFive () << '\n'; //imprime 5
    std::cout << returnFive () + 2 << '\n';  //imprime 7
    returnFive (); // bien: se devuelve el valor 5, pero se ignra ya que main () no hace nada con él
    return 0;
    /*
    @Autor : Edgar Rodriguez Briseño
    @Fecha : 18/09/2023
    */ 
}