#include <iostream>

int main(){
    std::cout << "Introduzca un número:"; // pedir al usuario un número
    int x {}; //definir una variable x para obtener la entrada del usuario (e iniciarlizarla a cero)
    std::cin >> x;// obtiene el número del teclado y lo almacena en la variable x
    std::cout << " Ingresastes " << x << '\n';
    return 0;
    /*
    @Autor : Edgar Rodriguez Briseño
    @Fecha : 14/09/2023
    */ 
}