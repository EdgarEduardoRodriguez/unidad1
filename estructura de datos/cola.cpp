#include <iostream>


const int capacidad = 5; // Capacidad de la cola
int cola[capacidad];     // Array para almecenar la cantidad
// se declaran ambos punteros para saber si la cola esta vacia
int frente = -1;         // Puntero al frente de la cola
int trasera = -1;        // Puntero a la parte trasera de la cola

//funcion para mostrar el estado de la cola
void mostrarEstadoCola(){
    if(frente == -1 && trasera == -1){// verifica si la cola esta vacia con los punteros
        std::cout << "Cola vacía, no hay elementos agregados." << std::endl;
    } else if ((trasera + 1) % capacidad == frente){// verifica si se puede agregar otro elemento si la cola tiene los 5 elementos la posicion de tresera es 4 se le suma 1
        std::cout << "Cola llena, la cola ha llegado al limite." << std::endl;// MOD de 5 (4 + 1) % 5  == frente = 0 ahi se colocara el otro elemento lo cual indica que esta llena 
    } else {
        std::cout << "Cola con espacio, aún se pueden agregar elementos." << std::endl;
    }
}

void mostrarCola() {
    if (frente == -1 && trasera == -1){// verifica si hay elementos en la cola
        std::cout << "Cola vacía, no hay elementos agregados." << std::endl;
        return;
    }

    std::cout << "Elementos en la cola: ";
    for (int i = frente; i != trasera; i = (i + 1) % capacidad){// este for continuara mientras i sea difeente de trasera que i es frente 
                                                                // i = (i + 1) % capacidad en cada iteracion i se sumara 1 y luego % capacidad asegura que vuelva al inicio de la cola si alcanza su capacidad máxima 
        std::cout << cola[i] << " ";// muestra los datos de la cola
    }
    std::cout << cola[trasera] << std::endl;// muestra el elemento agregado 
    mostrarEstadoCola();// muestra como se encuentra la cola
}

//funcion para agregar datos a la cola 
void agregar(int elemento) {
    if ((trasera + 1) % capacidad == frente) {// checa si la cola esta llena 
        std::cout << "Cola llena, no se pueden agregar más elementos." << std::endl;
    } else {
        if (frente == -1 && trasera == -1) {// checa si la cola esta vacia si esta vacia poene el valor agregado en
            frente = 0;                     // en los punteros frente 0 y trasera 0
            trasera = 0;
        } else {
            trasera = (trasera + 1) % capacidad;// se agrega el elemento en la nueva posicion de trasera
        }

        cola[trasera] = elemento;// asignacion del elemento
        mostrarCola();
    }
}

void quitar() {
    if (frente == -1 && trasera == -1) {// checa si la cola esta vacia
        std::cout << "Cola vacía, no se pueden quitar más elementos." << std::endl;
    } else {
        std::cout << "Quitando elemento: " << cola[frente] << std::endl;

        if (frente == trasera) {// si hay un solo elemento en la cola se reinicia la cola con los valores -1
            frente = -1;
            trasera = -1;
        } else {
            frente = (frente + 1) % capacidad;// despues de quitar el elemento se recorre a la nueva posicion de frente
        }

        mostrarCola();
    }
}


void limpiarCola() {
    if (frente == -1 && trasera == -1) {// checa si la cola esta vacia
        std::cout << "No hay elementos para limpiar en la cola." << std::endl;
    } else {
        frente = -1;// vuelve al estado de vacia de la cola
        trasera = -1;
        std::cout << "Cola limpiada." << std::endl;
        mostrarCola();
    }
}

int main() {
    int opcion, valor;

    do {
        std::cout << "Menú de operaciones:" << std::endl;
        std::cout << "1. Agregar un elemento" << std::endl;
        std::cout << "2. Quitar un elemento" << std::endl;
        std::cout << "3. Limpiar cola" << std::endl;
        std::cout << "4. Mostrar estado de la cola" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                std::cout << "Ingrese el valor a agregar a la cola." << std::endl;
                std::cin >> valor;
                agregar(valor);
                break;
            case 2:
                quitar();
                break;
            case 3:
                limpiarCola();
                break;
            case 4:
                mostrarCola();
                break;
            case 5:
                std::cout << "Saliendo del programa." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
        }
    } while (opcion != 5);

    return 0;
}

