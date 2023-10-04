#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <limits>

// Definición de la estructura para representar un evento
struct evento {
    std::string nombres;
    int dia, mes, año, hora, minuto;
};

int obtenerEnteroValido() {//para que el usuario no ingrese letras
    int numero;
    while (!(std::cin >> numero)) {
        std::cin.clear();// esta para borrar caulquier tipo de error
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Carácter no válido. Ingrese un número." << std::endl;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // esta linea sirve para limpiar el buffer de entrada para que no queden carateres no deseados
    return numero;//devuelve el numero ENTERO deseado
}

// Función para validar si una fecha es válida
bool esFechaValida(int dia, int mes, int año) {
    if (mes < 1 || mes > 12) {
        return false; // Mes no válido
    }
    if (dia < 1 || dia > 31) {
        return false; // Día no valido
    }
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) {
        return false; // Meses con 30 días
    }
    if (mes == 2) {
        if ((dia > 29) || (dia > 28 && ((año % 4 != 0) || (año % 100 == 0 && año % 400 != 0)))) {
            return false; // Para ver si es un año bisiesto
        }
    }
    return true; // La fecha es válida
}

// Función para validar si una hora es válida
bool esHoraValida(int hora, int minuto) {
    return (hora >= 0 && hora < 24 && minuto >= 0 && minuto < 60);
}
// Función para calcular la hora de diferencia
void calcularTiempo(const evento& ev){// const event& ev lo toma como parametro para que no se haga una copia inecesaria de datos
    time_t ahora = time(0);
    tm eventoTime = {};
    eventoTime.tm_year = ev.año - 1900;
    eventoTime.tm_mon = ev.mes - 1;
    eventoTime.tm_mday = ev.dia;
    eventoTime.tm_hour = ev.hora;
    eventoTime.tm_min = ev.minuto;
    eventoTime.tm_sec = 0;

    time_t eventoTiempo = mktime(&eventoTime);
    double segundosRestantes = difftime(eventoTiempo, ahora);

    if (segundosRestantes < 0) {
        std::cout << "El evento \"" << ev.nombres << "\" ya ha pasado" << std::endl;
    } else {
        const int segundosEnMinuto = 60;
        const int segundosEnHora = 3600;
        const int segundosEnDia = 86400;
        const int segundosEnMes = 2592000; 
        const int segundosEnAño = 31536000;

        int añosRestantes = static_cast<int>(segundosRestantes / segundosEnAño); // Divide segundos en años
        segundosRestantes -= añosRestantes * segundosEnAño;

        int mesesRestantes = static_cast<int>(segundosRestantes / segundosEnMes); // Divide segundos en meses
        segundosRestantes -= mesesRestantes * segundosEnMes;

        int diasRestantes = static_cast<int>(segundosRestantes / segundosEnDia); // Divide segundos en días
        segundosRestantes -= diasRestantes * segundosEnDia;

        int horasRestantes = static_cast<int>(segundosRestantes / segundosEnHora); // Divide segundos en horas
        segundosRestantes -= horasRestantes * segundosEnHora;

        int minutosRestantes = static_cast<int>(segundosRestantes / segundosEnMinuto); // Convierte segundos en minutos

        std::cout << "Tiempo restante para el evento \"" << ev.nombres << "\":" << std::endl;
        if (añosRestantes > 0) {
            std::cout << añosRestantes << " año(s) ";
        }
        if (mesesRestantes > 0) {
            std::cout << mesesRestantes << " mes(es) ";
        }
        if (diasRestantes > 0) {
            std::cout << diasRestantes << " día(s) ";
        }
        if (horasRestantes > 0) {
            std::cout << horasRestantes << " hora(s) ";
        }
        if (minutosRestantes > 0) {
            std::cout << minutosRestantes << " minuto(s) ";
        }
        if (añosRestantes == 0 && mesesRestantes == 0 && diasRestantes == 0 && horasRestantes == 0 && minutosRestantes == 0) {
            std::cout << "El evento es ahora";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<evento> agenda; // Declaración del vector llamado agenda para guardar los eventos

    while (true) {
        std::cout << "MENU DE OPCIONES" << std::endl;
        std::cout << "1. Agregar un evento" << std::endl;
        std::cout << "2. Mostrar todos los eventos" << std::endl;
        std::cout << "3. Mostrar tiempo para el evento" << std::endl;
        std::cout << "4. Eliminar un evento" << std::endl; // Opción para eliminar eventos
        std::cout << "5. Editar un evento" << std::endl;   // Opción para editar eventos
        std::cout << "6. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";

        int opc = obtenerEnteroValido();

        evento evento; // Declaración de una variable evento para guardar temporalmente los datos de un evento

        switch (opc) {
            case 1: // Agregar eventos
                std::cout << "Ingrese el nombre del evento: ";
                    std::cout << "Ingrese el nombre del evento: ";
                std::getline(std::cin, evento.nombres);
                while (true) {
                    std::cout << "Ingrese la fecha del evento (días/meses/años): ";
                    char separador; // Variable para almacenar el carácter separador ("/")
                    if (!(std::cin >> evento.dia >> separador >> evento.mes >> separador >> evento.año) || separador != '/') {
                        std::cout << "Formato de fecha no válido. Use el formato días/meses/años (por ejemplo, 12/9/23)." << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;
                    }

                    if (esFechaValida(evento.dia, evento.mes, evento.año)) {
                        break;
                    } else {
                        std::cout << "Fecha no válida. Ingrese otra fecha." << std::endl;
                    }
                }

                while (true) {
                    std::cout << "Ingrese la hora del evento (0-23): ";
                    evento.hora = obtenerEnteroValido();
                    std::cout << "Ingrese los minutos del evento (0-59): ";
                    evento.minuto = obtenerEnteroValido();

                    if (esHoraValida(evento.hora, evento.minuto)) {
                        break;
                    } else {
                        std::cout << "Hora no válida. Ingrese otra hora." << std::endl;
                    }
                }

                agenda.push_back(evento); // Lo agrega al vector
                break;
            case 2: // Mostrar eventos
                if (!agenda.empty()) {
                    std::cout << "Lista de Eventos:" << std::endl;
                    for (int i = 0; i < agenda.size(); i++) {
                        std::cout << "Evento " << i + 1 << ": " << agenda[i].nombres << " Fecha: " << agenda[i].dia << "/" << agenda[i].mes << "/" << agenda[i].año
                                  << " Hora: " << agenda[i].hora << ":" << agenda[i].minuto << std::endl;
                    }
                } else {
                    std::cout << "No hay eventos para mostrar" << std::endl;
                }
                break;
            case 3: // Calcular tiempo para el evento
                if (!agenda.empty()) {
                    std::cout << "Ingrese el número de evento: ";
                    int numEvento = obtenerEnteroValido();

                    if (numEvento >= 1 && numEvento <= agenda.size()) {
                        calcularTiempo(agenda[numEvento - 1]);// llama a la funcion donde esta para calcular la hora le damos en valor a parametro  a agenda[numEvento -1]
                        
                    } else {
                        std::cout << "Número de evento no válido" << std::endl;
                    }
                } else {
                    std::cout << "No hay eventos para mostrar" << std::endl;
                }
                break;
            case 4: // Eliminar evento
                if (!agenda.empty()) {
                    std::cout << "Ingrese el número de evento que desea eliminar: ";
                    int numEvento = obtenerEnteroValido();

                    if (numEvento >= 1 && numEvento <= agenda.size()) {
                        // Elimina el evento seleccionado del vector
                        agenda.erase(agenda.begin() + numEvento - 1);
                        std::cout << "Evento eliminado con éxito" << std::endl;
                    } else {
                        std::cout << "Número de evento no válido" << std::endl;
                    }
                } else {
                    std::cout << "No hay eventos para eliminar" << std::endl;
                }
                break;
            case 5: // Editar evento
                if (!agenda.empty()) {
                    std::cout << "Ingrese el número de evento que desea editar: ";
                    int numEvento = obtenerEnteroValido();

                    if (numEvento >= 1 && numEvento <= agenda.size()) {
                        std::cout << "Ingrese el nuevo nombre del evento: ";
                        std::getline(std::cin, agenda[numEvento - 1].nombres);

                        while (true) {
                            std::cout << "Ingrese la nueva fecha del evento (días/meses/años): ";
                            char separador;
                            if (!(std::cin >> agenda[numEvento - 1].dia >> separador >> agenda[numEvento - 1].mes >> separador >> agenda[numEvento - 1].año) || separador != '/') {
                                std::cout << "Formato de fecha no válido. Use el formato días/meses/años (por ejemplo, 12/9/23)." << std::endl;
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                continue;
                            }

                            if (esFechaValida(agenda[numEvento - 1].dia, agenda[numEvento - 1].mes, agenda[numEvento - 1].año)) {
                                break;
                            } else {
                                std::cout << "Fecha no válida. Ingrese otra fecha." << std::endl;
                            }
                        }

                        while (true) {
                            std::cout << "Ingrese la nueva hora del evento (0-23): ";
                            agenda[numEvento - 1].hora = obtenerEnteroValido();
                            std::cout << "Ingrese los nuevos minutos del evento (0-59): ";
                            agenda[numEvento - 1].minuto = obtenerEnteroValido();

                            if (esHoraValida(agenda[numEvento - 1].hora, agenda[numEvento - 1].minuto)) {
                                break;
                            } else {
                                std::cout << "Hora no válida. Ingrese otra hora." << std::endl;
                            }
                        }

                        std::cout << "Evento editado con éxito" << std::endl;
                    } else {
                        std::cout << "Número de evento no válido" << std::endl;
                    }
                } else {
                    std::cout << "No hay eventos para editar" << std::endl;
                }
                break;
            case 6: // Salir del programa
                std::cout << "Saliendo del programa" << std::endl;
                return 0;
            default:
                std::cout << "Opción no válida. Por favor, seleccione un número válido" << std::endl;
        }
    }

    return 0;
}