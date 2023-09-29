#include <iostream>

/*int mian()
{
    int foo () // ilegal esta funcion está anidada de la función mian()
    {
        std::cout<<"¡foo!\n";
    }

    foo (); //llamada de función a foo ()

    return 0;
}
*/
int foo() // no longer inside of main ()
{
    std::cout << "¡foo!\n";
    return 0;
}

int main()
{
    foo();

    return 0;
    /*
    @Autor : Edgar Rodriguez Briseño
    @Fecha : 18/09/2023
    */ 
}