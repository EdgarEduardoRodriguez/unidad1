#include <iostream>
#include <string>

using namespace std;

const int NUM_PERSONAS = 4;
const int NUM_PRODUCTOS = 7;

// Función para mostrar el menú de productos
void mostrarMenu() {
    cout << "Menú de Productos:" << endl;
    cout << "1. 1 Kg carne $300.00" << endl;
    cout << "2. Galletas maravilla $15.00" << endl;
    cout << "3. Los chetos $80.00" << endl;
    cout << "4. 1 Coca Cola 2 lts. $29.00" << endl;
    cout << "5. Lt Aceite Maceite $38.00" << endl;
    cout << "6. 1 Kg Maseca $16.00" << endl;
    cout << "7. 1 Kg Machaca $421.00" << endl;
}

int main() {
    //DECLARACION DE MATRICES
    string nombres[NUM_PERSONAS];
    string menuYcompras[NUM_PRODUCTOS] = {"1. 1 Kg carne $300.00", "2. Galletas maravilla $15.00","3. Los chetos $80.00", "4. 1 Coca Cola 2 lts. $29.00","5. Lt Aceite Maceite $38.00","6. 1 Kg Maseca $16.00","7. 1 Kg Machaca $421.00" };
    string productosComprados[NUM_PERSONAS][NUM_PRODUCTOS];
    //ESTA MATRIZ SIRVE PARA ALMACENAR LOS PRECIOS
    double precios[NUM_PRODUCTOS] = {300.00, 15.00, 80.00, 29.00, 38.00, 16.00, 421.00};
    //ESTA SIRVE PARA ALMACENAR LOS PRODUCTOS QUE SE COMPRARON
    double totales[NUM_PERSONAS][1];
     mostrarMenu();
    // Ingresar nombres de los compradores
    for (int i = 0; i < NUM_PERSONAS; i++) {
        cout << "Ingrese el nombre del comprador " << i + 1 << ": ";
        getline(cin, nombres[i]);
        
    }

    // Ingresar compras
    for (int i = 0; i < NUM_PERSONAS; i++) {
        cout << "Compras de " << nombres[i] << ":" << endl;
        for (int j = 0; j < NUM_PRODUCTOS; j++) {
            double cantidad;
            cout << "Cantidad de producto " << menuYcompras[j] << ": ";//menuYcompras llama ala matriz donde esta almacenado los productos para mostrarlos
            cin >> cantidad;
            if (cantidad > 0) { //AQUI SE MOSTRARA LA CANTIDAD QUE SE COMPRO DE CADA PRODUCTO DEL MENU 
                productosComprados[i][j] = to_string(cantidad) + " x Producto " + to_string(j + 1);
                totales[i][j] += cantidad * precios[j];
            }
        }
    }

    //mostrar historial de compras de cada cliente o compradores
    cout << "Resumen de Compras:" << endl;
    for(int i = 0; i < NUM_PERSONAS; i++){
        cout << "Comprador " << i + 1 << " " << nombres[i] << " total: $" << totales[i][0] << endl;
    }

    //Mostrar el total final vendido 
    double totalFinal = 0;
    for(int i = 0; i < NUM_PERSONAS; i++)
    {
        totalFinal += totales[i][0];
    }
    cout << "Total Final Vendido: $" << totalFinal << endl;
    return 0;
}