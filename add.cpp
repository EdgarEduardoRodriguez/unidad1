#include <iostream>
#include <string>

int main() {
    std::string texto;
    
    // Leer una línea de texto desde la entrada estándar (teclado)
    std::cout << "Ingresa una línea de texto: ";
    std::getline(std::cin, texto);
    
    // Mostrar el texto ingresado
    std::cout << "El texto ingresado es: " << texto << std::endl;

    return 0;
}