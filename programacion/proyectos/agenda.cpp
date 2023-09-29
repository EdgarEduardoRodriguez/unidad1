#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <limits>

// Definición de la estructura para representar un evento
struct evento {
    std::string nombres;
    int dia, mes, año;
};

int obtenerEnteroValido(){//para que el usuario no ingrese letras
    int numero;
    while (!(std::cin >> numero)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << " Tecla incorrecta. Ingrese un número válido";
    }
    return numero;
}
// Función para validar si una fecha es válida
bool esFechaValida(int dia, int mes, int año) {
    if (mes < 1 or mes > 12) {
        return false; // Mes fuera de rango
    }
    if (dia < 1 or dia > 31) {
        return false; // Día fuera de rango
    }
    if ((mes == 4 or mes == 6 or mes == 9 or mes == 11) && dia > 30) {
        return false; // Meses con 30 días
    }
    if (mes == 2) {
        if ((dia > 29) or (dia > 28 and ((año % 4 != 0) || (año % 100 == 0 && año % 400 != 0)))) {
            return false; // Febrero (considerando años bisiestos)
        }
    }
    return true; // La fecha es válida
}

int main() {
    std::vector<evento> agenda; // Declaración del vector llamado agenda para guardar los eventos

    while (true) {
        std::cout << "MENU DE OPCIONES" << std::endl;
        std::cout << "1.Agregar un evento" << std::endl;
        std::cout << "2.Mostrar todos los eventos" << std::endl;
        std::cout << "3.Mostrar tiempo para el evento" << std::endl;
        std::cout << "4.Salir" << std::endl;
        std::cout << "Seleccione una opción: ";

        int opc = obtenerEnteroValido();

        evento evento; // Declaración de una variable evento para guardar temporalmente los datos de un evento

        switch (opc) {
            case 1: // Agregar eventos
                std::cout << "Ingrese el nombre del evento: ";
                std::cin.ignore(); // Ignorar el salto de línea anterior
                std::getline(std::cin, evento.nombres);
                std::cout << "Ingrese el día del evento: ";
                evento.dia = obtenerEnteroValido();
                std::cout << "Ingrese el mes del evento: ";
                evento.mes = obtenerEnteroValido();
                if(!esFechaValida(evento.dia, evento.mes, evento.año)){
                    std::cout << "Fecha no aálida. Ingrese otra fecha" << std::endl;
                    continue;
                }
                std::cout << "ingrese el año del evento: ";
                evento.año = obtenerEnteroValido();
                if(!esFechaValida(evento.dia, evento.mes, evento.año)){
                    std::cout << "Fecha no válida. Ingrese otra fecha" << std::endl;
                    continue;
                }
                
                agenda.push_back(evento);// lo agrega al vector
                break;
            case 2: // Mostrar eventos
                if (!agenda.empty()) { // Verificar si hay eventos en la agenda
                    std::cout << "Lista de Eventos:" << std::endl;
                    for (int i = 0; i < agenda.size(); i++) { // Recorrer y mostrar todos los eventos almacenados
                        std::cout << "Evento " << i + 1 << ": " << agenda[i].nombres << " Fecha: " << agenda[i].dia << "/" << agenda[i].mes << "/" << agenda[i].año << std::endl;
                    }
                } else {
                    std::cout << "No hay eventos para mostrar" << std::endl;
                }
                break;
            case 3: // Calcular tiempo para el evento
                if (!agenda.empty()) { // Verificar si hay eventos en la agenda si esta vacio el operador ! lo nega, por lo que este bloque se ejecutará si hay eventos en la agenda 
                    std::cout << "Ingrese el número de evento: ";
                    int numEvento = obtenerEnteroValido();// variable que se utilizara para leer el numero del evento que el usuario quiere consultar

                    if (numEvento >= 1 && numEvento <= agenda.size()) { // Verificar si el número del evento es valido y si el tamaño de la agenda es valido
                        time_t ahora = time(0); // obtiene la hora actual del sistema y la guarda en la variable ahora
                        tm eventoTime = {}; // se declara una estructura esta sirve para representar la fecha y la hora del evento
                        eventoTime.tm_year = agenda[numEvento - 1].año - 1900;// se le resta al 1900 al año por la estructura "tm" si ingresa 2023 se le resta 1900 y queda 123  y asi lo leé
                        eventoTime.tm_mon = agenda[numEvento - 1].mes - 1;
                        eventoTime.tm_mday = agenda[numEvento - 1].dia;

                        time_t eventoTiempo = mktime(&eventoTime);// la estructurra eventoTime se convierte en un valor de tiempo(time_t) que representa la fecha y hora del evento y la función "mktime" realiza esta conversión
                        double segundosRestantes = difftime(eventoTiempo, ahora);// esto calcula la diferencia de segundos entre el tiempo del evento "eventoTiempo" y el tiempo actual "ahora" que dise cuantos segundos faltan para que ocurra el evento 

                        if (segundosRestantes < 0) { //verifica si los segundos menores a cero 
                            std::cout << "El evento " << agenda[numEvento - 1].nombres << " ya ha pasado" << std::endl;// si los segundos estan por debajo de 0 osea va mostrar este mensaje 
                        } else {
                            int diasRestantes = static_cast<int>(segundosRestantes / 86400); // se declara una variable diasRestantes donde se le pone valor a segundosRestantes dividido 86400 que son los segundos que tiene el dia 
                            int añosRestantes = diasRestantes / 365;
                            int mesesRestantes = (diasRestantes % 365) / 30;
                            int diasRestantesFinales = (diasRestantes % 365) % 30;
                            
                            if (añosRestantes > 0) {
                                std::cout << añosRestantes << " años(s) ";
                            }
                            if (mesesRestantes > 0){
                                std::cout << mesesRestantes << " mes(es) ";
                            }
                            if (diasRestantesFinales > 0){
                                std::cout << diasRestantesFinales << " día(s)";
                            }
                            std::cout << std::endl;

                        }
                    } else {// si selecciona un evento que no es muestra este mensaje 
                        std::cout << "Número de evento no válido" << std::endl;
                    }
                } else {
                    std::cout << "No hay eventos para mostrar" << std::endl;
                }
                break;
            case 4: // Salir del programa
                std::cout << "Saliendo del programa" << std::endl;
                return 0;
            default:
                std::cout << "Opción no válida. Por favor, seleccione un número válido" << std::endl;
        }
    }

    return 0;
}