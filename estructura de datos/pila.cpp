#include <iostream>

const int capacidad = 5;// la capacidad de la pila
int elementos[capacidad]; // declaracion del areglo 

int  tope = -1; // variable para saber la parte superior de la pila

void mostrarEstadoPila();// se decalara esto aqui por que si no da error por que lo llama antes de ser declarada

void mostrarPila(){// funcion para mostrar pila
    std::cout << "Elementos en la pila: " << std::endl;
    for (int i = tope; i >= 0; --i){// ciclo for para mostrar la pila desde la parte superior hacia abajo con "--i"
        std::cout << elementos[i] << std::endl;// muestra los elementos de la pila
    }
    mostrarEstadoPila();// muestra el estado de la pila
}

void push(int elemento) {// agrega un elemento a la pila
    if(tope < capacidad - 1){// verifica si la pila tiene espacio evalua si la posiscion actual del tope es menor a cpacidad - 1 evalua eso si se cumple añade un elemento
        elementos[++tope] = elemento;// 
        mostrarPila();// muestra la pila
    } else {// si la pila no tiene estapacio 
        std::cout << "pila llena, no se puedem agregar más elementos." << std::endl;
    }
}

void pop() {// funcion para quitar un elemento a la pila
    if(tope >= 0){// si tope es igual o mayor a cero se puden agregar elementos verifica si la pila no esta vacia 
        --tope;// elemina una variable de la parte superior de la pila igual como se añade "--i" igual se quita "--tope"
        mostrarPila();// muestra la pila
    } else {// si esta vacia 
        std::cout << "Pila vacía, nose pueden quitar elementos." << std::endl;
    }
}

void limpiarPila() {// funcion para limpiar la pila 
    if(tope >= 0){// igual que la funcion de arriba verifica si la pila esta vacia 
        mostrarPila();// muestra la pila antes de ser eleminada 
        tope = -1;// elimina los datos de la pila vuelve al arreglo hasta la posicion -1 que no hay nada
        mostrarPila();// muestra el estado de la pila despues de ser eleminada 
    } else {
        std::cout << "No hay elementos para limpiar en la pila." << std::endl;
    }
}

void mostrarEstadoPila() {// muestra como se encuentra la pila 
    if (tope == -1) {// si tope == -1 la pila esta vacia 
        std::cout << "Pila vacía, no hay elementos agregados." << std::endl;
    } else if (tope == capacidad - 1) {// si tope esta esta en la posicion 4 entonces la pila esta llena 
        std::cout << "Pila llena, la pila ha llegado a su tope." << std::endl;
    } else {// si ninguna de las otras entonces la pila tiene espacio
        std::cout << "Pila con espacio, aún se pueden ingresar valores." << std::endl;
    }
}


int main() {
    int opcion, valor;

    do {
        std::cout << "Menú de operaciones:" << std::endl;
        std::cout << "1. Insertar un elemento" << std::endl;
        std::cout << "2. Quitar un elemento" << std::endl;
        std::cout << "3. Limpiar pila" << std::endl;
        std::cout << "4. Mostrar estado de la pila" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                std::cout << "Ingrese el valor a insertar: ";
                std::cin >> valor;
                push(valor);
                break;
            case 2:
                pop();
                break;
            case 3:
                limpiarPila();
                break;
            case 4:
                mostrarPila();
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