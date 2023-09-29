#include <iostream>
#include <string>

using namespace std;

string unidades[] = {"uno","dos","tres","cuatro","cinco","seis","siete","ocho","nueve"};
string decenas[] = {"diez","veinte","treinta","cuarenta","cincuenta","sesenta","setenta","ochenta","noventa"};
string anormales[] = {"diez","once","doce","trece","catorce","quince","dieciséis","diecisiete","dieciocho","diecinueve"};
string meses[] = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};
// Funcion para convertir un número en numero en letras
string numerosEnLetras(int numero){
    if (numero >= 1 and numero <= 9){
        return unidades[numero - 1];
    } else if (numero >= 10 and numero <= 19){
        return anormales[numero - 10];
    } else if (numero % 10 == 0){
        return decenas[numero / 10 - 1];
    } else {
        return decenas[numero / 10 - 1] + " y " + unidades[numero % 10 - 1];
    }
}
//funcion para años
string añoEnLetras(int año){
    if (año >= 2000){
        return "dos mil " + numerosEnLetras(año - 2000);
    } else if (año >= 1900){
        return "mil novecientos " + numerosEnLetras(año - 1900);
    } else {
        return "Año no soportado";
    }
}

int main() {
    const int capacidad = 1;//capacidad del array
    //declarar la array
    string nombres[capacidad];
    string ap[capacidad];
    string am[capacidad];
    int diaDeNacimiento[capacidad];
    int mesDeNacimiento[capacidad];
    int añoDeNacimiento[capacidad];
    //ciclo for para inciar a preguntar al usuario
    for(int i = 0; i < capacidad; i++){
        cout << "Ingrese el nombre del amigo " << i + 1 << ": ";
        getline(cin, nombres[i]);

        cout << "Ingrese el apellido paterno del amigo " << i + 1 << ": ";
        getline(cin, ap[i]);

        cout << "Ingrese el apellido materno del amigo " << i + 1 << ": ";
        getline(cin, am[i]);

        cout << "Ingrese el día de nacimiento del amigo " << i + 1 << ": ";
        cin >> diaDeNacimiento[i];

        cout << "Ingrese el mes de nacimiento del amigo " << i + 1 << " (1-12): ";
        cin >> mesDeNacimiento[i];

        cout << "Ingrese el año de nacimiento del amigo " << i + 1 << ": ";
        cin >> añoDeNacimiento[i];

        cin.ignore(); // Limpia el buffer después de leer un número
    }
    //ciclo para mostrar los datos 
    for (int i = 0; i < capacidad; i++){
        //damos valor a las funciones con otras variables
        string diaEnLetras = numerosEnLetras(diaDeNacimiento[i]);
        //en esta llamamos a una array
        string mesEnLetras = meses[mesDeNacimiento[i] - 1];
        string añosEnLetrasCompleto = añoEnLetras(añoDeNacimiento[i]);

        string variableFinal = nombres[i] + " " + ap[i] + " " + am[i] + " nació el " + diaEnLetras + " de " + mesEnLetras + " del " + añosEnLetrasCompleto;

        cout << variableFinal << endl;
    }

    return 0;
}




