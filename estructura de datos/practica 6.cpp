#include <iostream>
#include <vector>
#include <set>
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
    int n = array.size(); // se obtiene el tamaño del vector y se almacena en "n"
    for (int i = 0; i < n - 1; i++) {// en este ciclo for se ejecuta en n - 1 mira si el elemento mas grande esta en su posicion correcta
        for (int j = 0; j < n - i - 1; j++) {// este for sirve para saber si el numero mas grande ya esta en su lugar y no necesita compararlo nuevamente
            if (array[j] > array[j + 1]) { // este if sirve para intercambair los valores por ejemplo posicion j son el elemento en la posicion j + 1 si el elemento en j es mayor que el elemeneto en j + q se intercambia 
                // intercambiar los elementos si están en el orden incorrecto
                std::swap(array[j], array[j + 1]);// swap es para intercambiar si se cumple la condicion arriba 
            }
        }
    }
}
void SinRepetir(std::vector<int>& array, int tamano) {// declaracion de funcion para no repetir numeros 
    std::set<int> numerosGenerados; // conjunto para rastrear los números generados
    std::srand(static_cast<unsigned>(std::time(nullptr))); // para no sean numeros con signo osea que no esten en negativo
                                                           // el time agarra de la computadora para hacer una secuencia de numeros aleatorios 
    for (int i = 0; i < tamano; i++) {// este for es para hacer la secuancia del 0 al 9999 que esta registrado en la variable tamaño
        int numeroAleatorio;
        do {
            numeroAleatorio = std::rand() % tamano;// secuencia de numeros aleatorios
        } while (numerosGenerados.count(numeroAleatorio) > 0);// hacer hasta que el numero sea mayor a 0

        numerosGenerados.insert(numeroAleatorio);// se asegura de que no se repitan los numeros futura interación
        array[i] = numeroAleatorio; // pone los numeros generados al array 
    }
}

// Función de partición para Quick Sort
int particion(std::vector<int>& array, int bajo, int alto) {// toma un vector y tambien toma los indices bajo y altop que van a representar la porcion del vector que se va a particionar (dividir)
    int pivote = array[alto]; // toma el último elemento como pivote que se utilizara para divdir el vector en dos partes
    int i = bajo - 1; // toma el primer elemento se va a utilizar para saber donde la posicion donde se establecera el pivote después de la partición

    for (int j = bajo; j <= alto - 1; j++) {// este ciclo for recorrera el vector de desde bajo hasta alto, comparara cada elemento con el pivote y realiza intercambios 
        if (array[j] < pivote) {// compara el elemento actual es menor que el pivote
            i++;// incrementa el elemento actual si es menor que el pivote
            std::swap(array[i], array[j]);// intercambia los elementos menores que esten a la izquierda 
        }
    }

    std::swap(array[i + 1], array[alto]);// despues de recorrer todo el vector intercambia el pivote con el elemento en la posicion siguinte de i y el pivote queda en su posicion final en el vector
    return i + 1;// deveulve la posición del pivote después de la partición
}

// Función de ordenamiento Quick Sort
void quickSort(std::vector<int>& array, int bajo, int alto) {
    if (bajo < alto) {// verifica si hay más de un elemento en la porción del vector que se esta ordenando
        
        int p = particion(array, bajo, alto);// le damos a p el valor de partición depues de esto p(partición) esta en su lugar final

        quickSort(array, bajo, p - 1);// ordena el pivote de la izquierda
        quickSort(array, p + 1, alto);// ordena la porcion del pivote de la derecha
    }
}

int main() {
    std::vector<int> array(30000);// declaracion del array
    
    
    SinRepetir(array, 30000); //llama a la funcion 
    
   

    double tiempoTranscurrido;// para alamacenar el tiempo en milisegundos 
    std::clock_t inicio, fin;// para registrar el tiempo 
    int posicion, clave;
    int limiteInferior, limiteSuperior;

    while (true) {
        std::cout << "Menú de opciones:" << std::endl;
        std::cout << "1. Mostrar vector" << std::endl;
        std::cout << "2. Realizar búsqueda binaria" << std::endl;
        std::cout << "3. Realizar metodo secuencial" << std::endl;
        std::cout << "4. Mostrar el vector ordenado por metodo burbuja" << std::endl;
        std::cout << "5. Mostrar el vector ordenado por metodo quickSort" << std::endl;
        std::cout << "6. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        
        int opcion;
        std::cin >> opcion;
        std::vector<int> v_desordenado (array);
        switch (opcion) {
            case 1:
                std::cout << "Vector: ";
                for (int valor : array ) {
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
                inicio = std::clock();// tomando el tiempo de inicio 
                ordenarBurbuja(v_desordenado);// ordenamiento del vector con metodo burbuja
                posicion = busquedaBinaria(v_desordenado, clave, limiteInferior, limiteSuperior);// llama a la funcion para la busqueda binaria
                fin = std::clock();// terminado el tiempo caundo acabe
                tiempoTranscurrido = static_cast<double>(fin - inicio) / CLOCKS_PER_SEC * 1000.0;// restamos fin - inicio y luego divimos en los ciclos de reloj de cpu a segunos y luego multiplicamos por 1000 para obtener los milisegundos 
                                              
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
                ordenarBurbuja(v_desordenado);// ordenamiento del vector con metodo burbuja
                bool encontrado = false;

                for (int i = 0; i < v_desordenado.size(); i++) {// declaracion de ciclo for para saber la posicion 
                    if (v_desordenado[i] == clave) { // guarda la posicion en donde encontro el resultado 
                        std::cout << "Se encontró el valor buscado en la posición " << i << std::endl;
                        encontrado = true;
                        break;
                    }
                }
                
                for (int i = 0; i < v_desordenado.size(); i++) {// se declara un for que rcorrerá array se ejecutar desde i = 0 hasta i sea menor que el tamaño del vector array
                    if (v_desordenado[i] == clave) {
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
                ordenarBurbuja(v_desordenado);
                for (int valor : v_desordenado) {
                    std::cout << valor << " ";
                }
                std::cout << std::endl;
                fin = std::clock();
                tiempoTranscurrido = static_cast<double>(fin - inicio) / CLOCKS_PER_SEC * 1000.0;
                std::cout << "Tiempo transcurrido de organizamiento del vector: " << tiempoTranscurrido << " milisegundos" << std::endl;
                break;
            case 5:
                inicio = std::clock();
                quickSort(v_desordenado, 0, v_desordenado.size() - 1);// llamamos al vector v_desordenado indice bajo 0 y indice alto como la cantidad de elemetos en el vector -1
                fin = std::clock();
            
                std::cout << "Vector ordenado después de Quick Sort: ";
                for (int valor : v_desordenado) {// ciclo para mostrar cada elemeto del vector
                    std::cout << valor << " ";
                }
                std::cout << std::endl;
            
                tiempoTranscurrido = static_cast<double>(fin - inicio) / CLOCKS_PER_SEC * 1000.0;
                std::cout << "Tiempo transcurrido de organizamiento del vector: " << tiempoTranscurrido << " milisegundos" << std::endl;
                break;
            case 6:
                std::cout << "Saliendo del programa." << std::endl;
                return 0;
            default:
                std::cout << "Opción no válida. Por favor, seleccione una opción válida." << std::endl;
                break;
        }
    }

    return 0;
}

