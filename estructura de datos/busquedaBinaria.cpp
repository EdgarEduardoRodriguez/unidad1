#include <iostream>
#include <vector>
// declaracion de la funcion donde esta la bsuqueda binaria 
int busquedaBinaria(const std::vector<int>& array, int clave, int& limiteInferior, int& limiteSuperior) {
    int bajo = 0;// se establecen parametros que bajo esta el la  posicion 0 del vector 
    int alto = array.size() - 1;// y este esta en la ultima parte del vector 
    
    while (bajo <= alto) { // se establece un ciclo while para saber que haye elementos en el rango de busqueda
        int central = (bajo + alto) / 2;// esta linea calcula el indice punto medio del array
        int valorCentral = array[central];// obtiene el valor del array central 
        
        if (clave == valorCentral) {// si la clave(el numero que ingreso el usuario) es igual al valor central 
            limiteInferior = bajo;// se le da el valor de bajo quie es la posicion de donde se encontro el valor 
            limiteSuperior = alto;// lo mismo pero el valor alto
            return central;  // devuelve la posicion central
        } else if (clave < valorCentral) {// si es central es menor que valorCentral
            alto = central - 1;// eso quiere decir que debe de estar en la mitad inferior del rango, por lo que alto apunta al elemento anterior 
        } else {// y si clave es mayor que valorCentral 
            bajo = central + 1;// debe de estar en la mitad superior del rango, por lo que "bajo" apunta al elemento siguiente 
        }
    }// y sigue continuando el mismo ciclo
    // si no se encuntra la clave se establece limiteInferior y superior en -1 para indicar que no se encontro la clave
    limiteInferior = -1;
    limiteSuperior = -1;
    return -1;// la funcion devuelve -1
}

int main() {
    //declaracion del vector 
    std::vector<int> array = {5, 8, 10, 13, 15, 18, 20, 23, 25, 29, 32, 36, 40, 42, 47, 51, 55, 63, 66};

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
                
                for (int i = 0; i < array.size(); i++) {// se declara un for que rcorrerá array se ejecutar desde i = 0 hasta i sea menor que el tamaño del vector array
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



