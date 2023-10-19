#include <iostream>
#include <vector>
// declaracion de la funcion donde esta la bsuqueda binaria 
int busquedaBinaria(int array, int clave, int& limiteInferior, int& limiteSuperior) {
    int bajo = 0;
    int alto = array - 1;
    
    while (bajo <= alto) {
        int central = (bajo + alto) / 2;
        int valorCentral = array[central];
        
        if (clave == valorCentral) {
            limiteInferior = bajo;
            limiteSuperior = alto;
            return central;  // Valor encontrado
        } else if (clave < valorCentral) {
            alto = central - 1;
        } else {
            bajo = central + 1;
        }
    }
    
    limiteInferior = -1;  // Valor no encontrado
    limiteSuperior = -1;
    return -1;
}

int main() {
    //declaracion del vector 
    int array = {5, 8, 10, 13, 15, 18, 20, 23, 25, 29, 32, 36, 40, 42, 47, 51, 55, 63, 66};

    while (true) {
        std::cout << "Menú de opciones:" << std::endl;
        std::cout << "1. Mostrar vector" << std::endl;
        std::cout << "2. Realizar búsqueda secuencial" << std::endl;
        std::cout << "3. Realizar búsqueda binaria" << std::endl;
        std::cout << "4. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        
        int opcion;
        std::cin >> opcion;
        
        if (opcion == 1) {
            std::cout << "Vector: ";
            for (int valor : array) {
                std::cout << valor << " ";
            }
            std::cout << std::endl;
        } else if (opcion == 2) {
            while (true) {
                std::cout << "Ingrese el valor a buscar (búsqueda secuencial): ";
                int clave;
                std::cin >> clave;
                
                bool encontrado = false;
                
                for (int i = 0; i < array; i++) {
                    if (array[i] == clave) {
                        std::cout << "Se encontró el valor buscado en la posición " << i << std::endl;
                        encontrado = true;
                        break;
                    }
                }
                
                if (!encontrado) {
                    std::cout << "Valor no encontrado." << std::endl;
                }
                
                std::cout << "¿Desea ingresar otro número? (1: Sí, 2: No): ";
                int decision;
                std::cin >> decision;
                
                if (decision != 1) {
                    break;
                }
            }
        } else if (opcion == 3) {
            while (true) {
                std::cout << "Ingrese el valor a buscar (búsqueda binaria): ";
                int clave;
                std::cin >> clave;
                
                int limiteInferior, limiteSuperior;
                int posicion = busquedaBinaria(array, clave, limiteInferior, limiteSuperior);
                
                if (posicion != -1) {
                    std::cout << "Se encontró el valor buscado en la posición " << posicion << std::endl;
                    std::cout << "Límite inferior: " << limiteInferior << std::endl;
                    std::cout << "Límite superior: " << limiteSuperior << std::endl;
                } else {
                    std::cout << "Valor no encontrado." << std::endl;
                }
                
                std::cout << "¿Desea ingresar otro número? (1: Sí, 2: No): ";
                int decision;
                std::cin >> decision;
                
                if (decision != 1) {
                    break;
                }
            }
        } else if (opcion == 4) {
            std::cout << "Saliendo del programa." << std::endl;
            break;
        } else {
            std::cout << "Opción no válida. Por favor, seleccione una opción válida." << std::endl;
        }
    }

    return 0;
}



