#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

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

void ordenarBurbuja(std::vector<int>& array) {
    int n = array.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                // intercambiar los elementos si están en el orden incorrecto
                std::swap(array[j], array[j + 1]);
            }
        }
    }
}

int main() {
    std::vector<int> array(200);
    
    // Llenar el vector con números aleatorios
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < 200; i++) {
        array[i] = std::rand() % 1000; // Números aleatorios entre 0 y 999
    }
    

    double tiempoTranscurrido;// para alamacenar el tiempo en milisegundos 
    std::clock_t inicio, fin;// para registrar el tiempo 
    int posicion, clave;
    int limiteInferior, limiteSuperior;

    while (true) {
        std::cout << "Menú de opciones:" << std::endl;
        std::cout << "1. Mostrar vector" << std::endl;
        std::cout << "2. Realizar búsqueda binaria" << std::endl;
        std::cout << "3. Realizar metodo secuencial" << std::endl;
        std::cout << "4. Mostrar el vector ordenado" << std::endl;
        std::cout << "4. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        
        int opcion;
        std::cin >> opcion;
        
        switch (opcion) {
            case 1:
                std::cout << "Vector: ";
                for (int valor : array) {
                    std::cout << valor << " ";
                }
                std::cout << std::endl;
                break;
            case 2:
            while(true){
                std::cout << "Ingrese el valor a buscar: ";
                std::cin >> clave;
                    
                limiteInferior = -1;
                limiteSuperior = -1;
                inicio = std::clock();
                ordenarBurbuja(array);// ordenamiento del vector con metodo burbuja
                posicion = busquedaBinaria(array, clave, limiteInferior, limiteSuperior);
                fin = std::clock();
                tiempoTranscurrido = static_cast<double>(fin - inicio) / CLOCKS_PER_SEC * 1000.0;
                    
                if (posicion != -1) {
                    std::cout << "Se encontró el valor buscado en la posición " << posicion << std::endl;
                    std::cout << "Límite inferior: " << limiteInferior << std::endl;
                    std::cout << "Límite superior: " << limiteSuperior << std::endl;
                    std::cout << "Tiempo transcurrido: " << tiempoTranscurrido << " milisegundos" << std::endl;
                } else {
                    std::cout << "Valor no encontrado." << std::endl;
                    std::cout << "Tiempo transcurrido: " << tiempoTranscurrido << " milisegundos" << std::endl;
                }
                std::cout << "¿Desea ingresar otro número? (1: Sí, 2: No): ";
                int decision;
                std::cin >> decision;
                
                if (decision != 1) {
                    break;
                }
            }
                break;
            case 3:
            while(true){
                std::cout << "Ingrese el valor a buscar (búsqueda secuencial): ";
                int clave;
                std::cin >> clave;

                inicio = std::clock();
                ordenarBurbuja(array);// ordenamiento del vector con metodo burbuja
                bool encontrado = false;

                for (int i = 0; i < array.size(); i++) {// declaracion de ciclo for para saber la posicion 
                    if (array[i] == clave) { // guarda la posicion en donde encontro el resultado 
                        std::cout << "Se encontró el valor buscado en la posición " << i << std::endl;
                        encontrado = true;
                        break;
                    }
                }
                
                for (int i = 0; i < array.size(); i++) {// se declara un for que rcorrerá array se ejecutar desde i = 0 hasta i sea menor que el tamaño del vector array
                    if (array[i] == clave) {
                        std::cout << "Se encontró el valor buscado en la posición " << i << std::endl;
                        encontrado = true;
                        break;
                    }
                }

                fin = std::clock();
                tiempoTranscurrido = static_cast<double>(fin - inicio) / CLOCKS_PER_SEC * 1000.0;
                
                if (!encontrado) {
                    std::cout << "Valor no encontrado." << std::endl;
                }

                    std::cout << "Tiempo transcurrido: " << tiempoTranscurrido << " milisegundos" << std::endl;

                std::cout << "¿Desea ingresar otro número? (1: Sí, 2: No): ";
                int decision;
                std::cin >> decision;
                
                if (decision != 1) {
                    break;
                }
            }

                break;
            case 4:
                std::cout << "Vector: ";
                inicio = std::clock();
                ordenarBurbuja(array);
                for (int valor : array) {
                    std::cout << valor << " ";
                }
                std::cout << std::endl;
                fin = std::clock();
                tiempoTranscurrido = static_cast<double>(fin - inicio) / CLOCKS_PER_SEC * 1000.0;
                std::cout << "Tiempo transcurrido de organizamiento del vector: " << tiempoTranscurrido << " milisegundos" << std::endl;
                break;
            case 5:
                std::cout << "Saliendo del programa." << std::endl;
                return 0;
            default:
                std::cout << "Opción no válida. Por favor, seleccione una opción válida." << std::endl;
                break;
        }
    }

    return 0;
}

