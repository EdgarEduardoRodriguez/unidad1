#include <iostream>
#include <vector>
#include <limits>

int obtenerEnteroValido() {
    int numero;
    while (!(std::cin >> numero)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Carácter no válido. Ingrese un número." << std::endl;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return numero;
}

// Función para sumar dos matrices
std::vector<std::vector<int>> sumarMatrices(const std::vector<std::vector<int>>& matriz1, const std::vector<std::vector<int>>& matriz2) {
    int filas = matriz1.size(); // filas se le da el valor de la matriz
    int columnas = matriz1[0].size(); // se le da el valor a columnas

    std::vector<std::vector<int>> resultado(filas, std::vector<int>(columnas, 0)); // creación de una matriz del mismo tamaño para guardar el resultado 

    // Paso a paso de la suma
    for (int i = 0; i < filas; ++i) { // recorre las filas de la matriz
        for (int j = 0; j < columnas; ++j) { // recorre las columnas de la matriz
            // Muestra la operación actual
            std::cout << "Suma de matriz 1[ fila " << i + 1 << "][ columna " << j + 1 << "] (" << matriz1[i][j] << ") y matriz 2[ fila " << i + 1 << "][ columna " << j + 1 << "] (" << matriz2[i][j] << "): ";

            // Realiza la suma y guarda el resultado en la matriz resultado
            resultado[i][j] = matriz1[i][j] + matriz2[i][j];

            // Muestra el resultado de la suma
            std::cout << "Resultado: " << resultado[i][j] << std::endl;
        }
    }

    return resultado;
}

// Función para restar dos matrices
std::vector<std::vector<int>> restarMatrices(const std::vector<std::vector<int>>& matriz1, const std::vector<std::vector<int>>& matriz2) {
    int filas = matriz1.size();
    int columnas = matriz1[0].size();

    std::vector<std::vector<int>> resultado(filas, std::vector<int>(columnas, 0));// declaracion de la matriz de resta 
    //esto hace lo mismo que la suma pero restando
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            std::cout << "Resta de matriz 1[fila: " << i + 1 << "][columna: " << j + 1 << "] (" << matriz1[i][j] << ") y matriz 2 [fila: " << i + 1 << "][columna: " << j + 1 << "] (" << matriz2[i][j] << "): ";
            
            resultado[i][j] = matriz1[i][j] - matriz2[i][j];
            
            std::cout << "Resultado: " << resultado[i][j] << std::endl;
        }
    }

    return resultado;
}

// Función para multiplicar dos matrices
std::vector<std::vector<int>> multiplicarMatrices(const std::vector<std::vector<int>>& matriz1, const std::vector<std::vector<int>>& matriz2) {
    int filas1 = matriz1.size();
    int columnas1 = matriz1[0].size();
    int filas2 = matriz2.size();
    int columnas2 = matriz2[0].size();

    // Verificar si las matrices son compatibles para la multiplicación
    if (columnas1 != filas2) {
        std::cout << "No se pueden multiplicar las matrices. Las dimensiones no son compatibles." << std::endl;
        return {}; // Devolver matriz vacía en caso de incompatibilidad
    }

    std::vector<std::vector<int>> resultado(filas1, std::vector<int>(columnas2, 0));

    // Realizar la multiplicación de matrices
    for (int i = 0; i < filas1; ++i) {
        for (int j = 0; j < columnas2; ++j) {
            // Inicializar la entrada en la posición (i, j) de la matriz resultado
            std::cout << "Multiplicando fila " << i + 1 << " de la matriz 1 por columna " << j + 1 << " de la matriz 2:" << std::endl;
            int sumaParcial = 0;
            for (int k = 0; k < columnas1; ++k) {
                // Mostrar los elementos multiplicados
                std::cout << "   " << matriz1[i][k] << " * " << matriz2[k][j] << " = " << matriz1[i][k] * matriz2[k][j] << std::endl;
                // Acumular el resultado parcial
                sumaParcial += matriz1[i][k] * matriz2[k][j];
            }
            // Mostrar la suma del resultado parcial
            std::cout << "Suma parcial en la posición (" << i + 1 << ", " << j + 1 << "): " << sumaParcial << std::endl;
            resultado[i][j] = sumaParcial;
            std::cout << std::endl;
        }
    }

    return resultado;
}



void mostrarMatriz(const std::vector<std::vector<int>>& matriz, const std::string& mensaje) {
    int filas = matriz.size();
    if (filas == 0) {
        std::cout << "La matriz está vacía. No se puede mostrar." << std::endl;
        return;
    }

    int columnas = matriz[0].size();

    std::cout << "Matriz " << mensaje << ":" << std::endl;
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Función para obtener la inversa de una matriz 2x2
std::vector<std::vector<int>> obtenerInversaMatriz2x2(const std::vector<std::vector<int>>& matriz) {
    double det = matriz[0][0] * matriz[1][1] - matriz[0][1] * matriz[1][0];
    double invDet = 1.0 / det;

    std::vector<std::vector<int>> inversaMatriz(2, std::vector<int>(2));

    inversaMatriz[0][0] = matriz[1][1] * invDet;
    inversaMatriz[0][1] = -matriz[0][1] * invDet;
    inversaMatriz[1][0] = -matriz[1][0] * invDet;
    inversaMatriz[1][1] = matriz[0][0] * invDet;

    return inversaMatriz;
}

std::vector<std::vector<int>> dividirMatrices(const std::vector<std::vector<int>>& matriz1, const std::vector<std::vector<int>>& matriz2) {
    // Obtener dimensiones de las matrices
    int filas1 = matriz1.size();
    int columnas1 = matriz1[0].size();
    int filas2 = matriz2.size();
    int columnas2 = matriz2[0].size();

    // Verificar si las matrices son compatibles para la división
    if (columnas1 != filas2) {
        std::cout << "No se pueden dividir las matrices. Las dimensiones no son compatibles." << std::endl;
        return {}; // Devolver matriz vacía en caso de incompatibilidad
    }

    // Comprobar si la matriz2 es invertible
    // Calcular la inversa de la matriz2 (solo para matrices 2x2)
    double det = matriz2[0][0] * matriz2[1][1] - matriz2[0][1] * matriz2[1][0];
    if (det == 0) {
        std::cout << "No se puede dividir. La matriz2 no es invertible." << std::endl;
        return {}; // Devolver matriz vacía en caso de matriz no invertible
    }

    double invDet = 1.0 / det;
    std::vector<std::vector<int>> inversaMatriz2(2, std::vector<int>(2));

    inversaMatriz2[0][0] = matriz2[1][1] * invDet;
    inversaMatriz2[0][1] = -matriz2[0][1] * invDet;
    inversaMatriz2[1][0] = -matriz2[1][0] * invDet;
    inversaMatriz2[1][1] = matriz2[0][0] * invDet;

    // Multiplicar la matriz1 por la inversa de la matriz2
    std::vector<std::vector<int>> resultado = multiplicarMatrices(matriz1, inversaMatriz2);

    // Mostrar el resultado paso a paso
    std::cout << "Paso a paso de la operación A / B:" << std::endl;

    mostrarMatriz(matriz1, "A");
    mostrarMatriz(matriz2, "B");
    mostrarMatriz(inversaMatriz2, "Inversa de B");

    std::cout << "Multiplicación de A por la inversa de B:" << std::endl;
    mostrarMatriz(resultado, "A * Inversa de B");

    return resultado; // Devolver el resultado de la división
}


// Función para ingresar los elementos de la matriz
void ingresarMatriz(std::vector<std::vector<int>>& matriz, int filas, int columnas) {
    std::cout << "Ingresa los elementos de la matriz:" << std::endl;

    for (int i = 0; i < filas; ++i) { //itera sobre cada fila y agrega una nueva fila a la matriz
        matriz.push_back(std::vector<int>(columnas));//en esta fila hace la agregación con ayuda del push_back

        for (int j = 0; j < columnas; ++j) {//itera sobre cada columna y solicita al usuario ingresar el elemento en la posicion de la matriz
            while (true) {
                std::cout << "Ingrese el elemento de la fila " << i + 1 << " columna " << j + 1 << ": ";// aqui solicita al usuario a ingresar el numero

                if (std::cin >> matriz[i][j]) {
                    // El usuario ingresó un número correctamente
                    break;
                } else {
                    // Hubo un error al ingresar el número
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Carácter no válido. Intente de nuevo." << std::endl;
                }
            }

            // Mostrar la matriz hasta el momento
            for (int k = 0; k <= i; ++k) {
                for (int l = 0; l < columnas; ++l) {
                    std::cout << matriz[k][l] << " ";//muestra los numeros que ya están en la matriz
                }
                std::cout << std::endl;
            }
        }
    }
}


void ingresarTamanioMatrices(int& filas, int& columnas) {
    std::cout << "Ingrese el tamaño de la columna de la matriz ";
    columnas = obtenerEnteroValido();
    std::cout << "Ingrese el tamaño de la fila de la matriz ";
    filas = obtenerEnteroValido();
}

int main() {
    int filas, columnas;
    int opcion;

    do {
        std::cout << "Elija la operación a realizar:" << std::endl;
        std::cout << "1. Suma" << std::endl;
        std::cout << "2. Resta" << std::endl;
        std::cout << "3. Multiplicación" << std::endl;
        std::cout << "4. División" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        std::vector<std::vector<int>> matriz1, matriz2, resultado;
        
        switch (opcion) {
            case 1:
            case 2:
            case 3:
            case 4:
                ingresarTamanioMatrices(filas, columnas);

                std::cout << "Matriz 1:" << std::endl;
                ingresarMatriz(matriz1, filas, columnas);

                std::cout << "Matriz 2:" << std::endl;
                ingresarMatriz(matriz2, filas, columnas);


                switch (opcion) {
                    case 1:
                        resultado = sumarMatrices(matriz1, matriz2);
                        mostrarMatriz(resultado, "suma de la matriz1 y la matriz2");
                        break;
                    case 2:
                        resultado = restarMatrices(matriz1, matriz2);
                        mostrarMatriz(resultado, "resta de la matriz1 y la matriz2");
                        break;
                    case 3:
                        resultado = multiplicarMatrices(matriz1, matriz2);
                        mostrarMatriz(resultado, "multiplicación de la matriz1 y la matriz2");
                        break;
                    case 4:
                        resultado = dividirMatrices(matriz1, matriz2);
                        mostrarMatriz(resultado, "división de la matriz1 y la matriz2");
                        break;
                }
                break;
            case 0:
                std::cout << "Saliendo del programa." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
        }

    } while (opcion != 0);

    return 0;
}


