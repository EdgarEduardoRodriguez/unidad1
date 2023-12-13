#include <iostream>

// Estructura para representar un nodo en la lista enlazada
struct Nodo {
    int dato;// dato almacena el valor del Nodo
    Nodo* siguiente;// siguiente almacena el puntero al siguiente nodo
};

// Inserta un elemento al final de la lista tipo FIFO en este caso solo para insertar elementos
void insertarElemento(Nodo*& frente, Nodo*& final, int valor) {// punteros del frente y final de la cola para poder modificarlo
    Nodo* nuevoNodo = new Nodo{valor, nullptr};// creacion del nuevo nodo con el valor proporcionado y un puntero siguiente inicializado a nullptr

    if (!frente) {
        // La lista está vacía, tanto frente como final apuntan al nuevo nodo
        frente = final = nuevoNodo;
    } else {// si la cola no esta vacia
        // Agregamos el nuevo nodo al final y actualizamos final
        final->siguiente = nuevoNodo;
        final = nuevoNodo;// se actauliza el puntero final para que apunte al nuevo nodo ya que es ahora el último de la nodo de la cola
    }

    // mostrar el elemento agregado
    std::cout << "Elemento " << valor << " insertado con éxito." << std::endl;

}

// Elimina un elemento específico de la cola
void eliminarElementoEspecifico(Nodo*& frente, Nodo*& final, int valor) {
    if (!frente) {
        std::cout << "La cola está vacía. No hay elementos para eliminar." << std::endl;
        return;
    }

    Nodo* actual = frente;// se actauliza el puntero actual para recorrer la cola comenzando desde el frente
    Nodo* anterior = nullptr;// se actualiza el puntero anterior para encontrar el nodo anterior al actial.
    // se establece en nullptr por que al inicio no hay un nodo anterior
    // Buscar el elemento en la cola
    while (actual && actual->dato != valor) {// este bucle recorre la cola hasta encontrar eel elemento a eliminar
        anterior = actual;// en el bucle while se actualiza el puntero anterior para que apunte al nodo actual antes de avanzar al siguiente nodo
        actual = actual->siguiente;// avanza el siguiente nodo en la cola en el puntero actual
    }

    if (!actual) {// si el ciclo while llega hasta el final es que no se encontro el numero
        // No se encontró el elemento en la cola
        std::cout << "El elemento " << valor << " no se encuentra en la cola." << std::endl;
        return;
    }

    if (actual == frente) {// checa si el elemento que va a elimnar es el primero en la cola
        // El elemento a eliminar es el primero de la cola
        frente = frente->siguiente;// si lo es actualiza el puntero frente para que apunte al siguiente nodo
        if (!frente) {
            // Si después de eliminar el elemento la cola queda vacía también actualizamos final
            final = nullptr;
        }
    } else {
        // El elemento a eliminar no es el primero de la cola
        anterior->siguiente = actual->siguiente;// conecta el nodo anterior al nodo actual con el siuiente nodo, saltandose asi el nodo actual y eleminandolo de la cola
        if (!actual->siguiente) {
            // Si el elemento a eliminar es el último de la cola, actualizamos final
            final = anterior;
        }
    }

    delete actual;// libera la memoria que ocupada por el nodo que conteien el elemento a eliminar

    // mostrar el elemento que elemino
    std::cout << "Elemento " << valor << " eliminado con éxito." << std::endl;

}

// Vacía la cola
void vaciarCola(Nodo*& frente, Nodo*& final) {
    if (!frente) { // checa si la cola esta vacia
        std::cout << "La cola está vacía. No hay elementos para vaciar." << std::endl;
        return;
    }

    while (frente) { // iniciamos un bucle que continuara mientras haya elementos en la cola
        Nodo* temp = frente; // crea un puntero temporal(temp) que apunta al primer nodo de la cola
        frente = frente->siguiente;// mueve el puntero "frente" al siguiente nodo se la cola 
        delete temp; // lo que esta arriba se prepara para este linea de codigo libera la memoria del nodo que aputa temp elimina todo
    }
    final = nullptr;// despues de vaciar todos los nodos establece el puntero final en nullptr para indicar que la cola esta vacia
    std::cout << "Cola vaciada con éxito." << std::endl;
}

// Busca un elemento en la cola
bool buscarElemento(Nodo* frente, int valor) {
    if (!frente) {// checa si la cola esta vacia 
        std::cout << "La cola está vacía. No se puede buscar ningún elemento." << std::endl;
        return false;
    }

    Nodo* actual = frente;// el puntero actual apunta al primer nodo de la cola

    while (actual) {// inicia un bucle while que se ejecutara mientras actual no sea nullptr (mientras que haya nodos en la cola)
        if (actual->dato == valor) {// compara el valor nodo actual con el valor que se esta buscando si son iguales se ha encontrado el elemento y devuelve true diciendo que ya se encontro
            return true; // El elemento se encuentra en la cola
        }
        actual = actual->siguiente;// mueve el puntero actual al siguiente nodo en la cola preparandolo para la proxima iteracion del bucle
    }
    // si  no se encontro el nodo buscado mostrara este mensaje
    std::cout << "El elemento no se encuentra en la cola." << std::endl;
    return false; // El elemento no se encuentra en la cola
}

// Muestra la cola en forma horizontal
void mostrarCola(const Nodo* frente) {
    if(!frente){
        std::cout << "Cola vacía." << std::endl;
        return;
    }
    
    std::cout << "Cola: ";
    const Nodo* temp = frente;// crea un puntero constante temp y lo inicializa en el primer nodo de la cola "frente"
    while (temp) {// este ciclo while se ejecutara mientras temp no sea nullptr (hasta que no haya nodos)
        std::cout << temp->dato << " ";// imprime el valor del nodo actual 
        temp = temp->siguiente;// recorre el puntero "temp" al siguiente nodo y seguira asi mientras haya nodos
    }
    std::cout << std::endl;
}

int main() {
    Nodo* frente = nullptr; // Puntero al primer nodo de la cola
    Nodo* final = nullptr;  // Puntero al último nodo de la cola
    int valor;
    int opcion;
    do {
        std::cout << "Menú:\n1. Insertar elemento\n2. Eliminar elemento\n3. Vaciar cola\n4. Mostrar cola\n5. buscar un elemento\n0. Salir\nIngrese su opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:// insertar elementos
                std::cout << "Ingrese el valor a insertar: ";
                std::cin >> valor;
                insertarElemento(frente, final, valor);
                mostrarCola(frente);
                break;
            case 2:// eleminar un elemento
                std::cout << "Ingrese el valor a eliminar: ";
                std::cin >> valor;
                eliminarElementoEspecifico(frente, final, valor);
                mostrarCola(frente);
                break;
            case 3:// vaciar todos los elementos
                mostrarCola(frente);
                vaciarCola(frente, final);
                mostrarCola(frente);
                break;
            case 4:// mostrar cola
                mostrarCola(frente);
                break;
            case 0:// salir del programa
                std::cout << "Saliendo del programa." << std::endl;
                break;
            case 5: // buscar elementos
                std::cout << "Ingrese el valor a buscar: ";
                std::cin >> valor;
                if (buscarElemento(frente, valor)) {
                    std::cout << "El elemento " << valor << " se encuentra en la cola." << std::endl;
                } else {
                    std::cout << "El elemento " << valor << " no se encuentra en la cola." << std::endl;
                }
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
        }

    } while (opcion != 0);

    return 0;
}
