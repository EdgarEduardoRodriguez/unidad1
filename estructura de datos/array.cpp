#include <iostream>
#include <string>

using namespace std;
string unidades[] = {"uno","dos","tres","cuatro","cinco","seis","siete","ocho","nueve"};
string decenas[] = {"diez","veinte","treinta","cuarenta","cincuenta","sesenta","setenta","ochenta","noventa"};
string anormales[] = {"diez","once","doce","trece","catorce","dieciséis","diesiciete","dieciocho","diecinueve"};
string meses[] = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};
// Funcion para convertir un número en numero en letras
string numerosEnLetras(int numero){
    if(numero >= 1 and numero <=9){//aqui si el numero es mayor o igual a 1 y menor o igual a 9 lo buscara en el arreglo unidades y si ese el caso se cumplira y si np se ira al siguiente if 
        return unidades[numero];
    } else if (numero >=10 and numero <=19){//es para buscar los numeros en el aray anormales
        return anormales[numero - 10];//aqui se resta -10 al numero para que pueda buscar el numero en el arreglo por ejemplo 11 se le resta 10 y que da uno y lo busca en la casilla 1 de l arreglo que es diez
    } else if (numero % 10 == 0){//aqui si el numero no ha pasado por los anteriores if si su residuo es es 0 se divide entre 10 y busca el numero en el array 
        return decenas[numero / 10];// se divide entre 10 por ejemplo 20/10 da 2 y va y lo busca en el array decenas que es dos 
    } else {// y si el if de arriba no se cumple se hace este else 
        return decenas[numero / 10] + " y " + unidades[numero % 10];//aqui se ponen los numeros que son decenas pero tienen un numero extra por ejemplo 21, 22, 23 si toma el 21 lo divide entre 10 y toma el 2 y se va al array de decenas que es 20
    }                                                               // despues se le coloca una " y " y luego toma el residuo del 21 que es 1 y se va al array de unidades y toma el uno y abra kadabra es veinte y uno 
}

//funcion para convertir el año a letras 
string añoEnLetras(int año){
    if (año >=2000){
        return "dos mil " + numerosEnLetras(año - 2000); //si el numero es mayor o igual a 2000 repite lo que esta en la funcion numeroEnLetras
    } else if (año >=1900){
        return "mil novecioentos " + numerosEnLetras(año - 1900);
    } else{
        return "Año no soportado";
    }
}
struct persona //paquete de datos para poder manipular msa facilmente
{
    string nombre, ap, am, dia, mes, año1; 
};


int main()
{
    const int capacidad = 1;// limita la capacidad del arreglo lo ponemos asi para mejor manipulación 
    persona amigo [capacidad];// inicialización del arreglo 
    //aqui empezamos a asignar los datos del arreglo 
    amigo[0]= {"juan carlos", "carreón", "soto", "18", "10","1998"}; // "nombre, ap, am, dia, mes, año"
    //aqui ingresamos las variables string diaEnLetras a las funciones el stoi(string to int) es para pasar al string al int 
    string diaEnLetras = numerosEnLetras(stoi(amigo[0].dia));
    string mesEnLetras = meses[stoi(amigo[0].mes) - 1]; // se le resta un 1 por que los arrays se inicializan en 0
    string añoEnLetrasCompleto = añoEnLetras(stoi(amigo[0].año1));

    string variableFinal = amigo[0].nombre + " " + amigo[0].ap + " " + amigo[0].am + " nació el " + diaEnLetras + " de " + mesEnLetras + " de " + añoEnLetrasCompleto;//varaible donde almacene todos los documentos 

    cout<< variableFinal;




    return 0;
}