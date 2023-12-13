#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <limits>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <sstream>

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

void obtenerFechaValida(int& dia, int& mes, int& año) {//funcion para preguntar la fecha y verificar si esta bien
    while (true) {
        std::cout << "Ingrese la fecha del evento (día/mes/año): ";
        char separador;
        if (!(std::cin >> dia >> separador >> mes >> separador >> año) || separador != '/') {
            std::cout << "Formato de fecha no válido. Use el formato día/mes/año (por ejemplo, 12/9/23)." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else if (!(mes >= 1 && mes <= 12 && dia >= 1 && dia <= 31)) {
            std::cout << "Fecha no válida. Ingrese otra fecha." << std::endl;
        } else if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) {
            std::cout << "Fecha no válida. Ingrese otra fecha." << std::endl;
        } else if (mes == 2) {
            if (dia > 29 || (dia > 28 && ((año % 4 != 0) || (año % 100 == 0 && año % 400 != 0)))) {
                std::cout << "Fecha no válida. Ingrese otra fecha." << std::endl;
            } else {
                break;
            }
        } else {
            break;
        }
    }
}

void obtenerHoraValida(int& hora, int& minuto) {//funcion para preguntar la hora y verificar si esta bien
    while (true) {
        std::string horaStr;
        std::cout << "Ingrese la hora del evento (HH:MM): ";
        std::cin >> horaStr;

        if (horaStr.size() == 5 && horaStr[2] == ':' && std::isdigit(horaStr[0]) && std::isdigit(horaStr[1]) && std::isdigit(horaStr[3]) && std::isdigit(horaStr[4])) {
            hora = std::stoi(horaStr.substr(0, 2));
            minuto = std::stoi(horaStr.substr(3, 2));
            if (hora >= 0 && hora < 24 && minuto >= 0 && minuto < 60) {
                break;
            }
        }
        std::cout << "Formato de hora no válido. Use el formato HH:MM (por ejemplo, 13:30)." << std::endl;
    }
}

// Función para calcular la hora de diferencia
void calcularTiempo(const evento& ev){// const event& ev lo toma como parametro para que no se haga una copia inecesaria de datos
    time_t ahora = time(0);// Obtiene la hora actual del sistema y la guarda en la variable ahora
    tm eventoTime = {};// Se declara una estructura que sirve para representar la fecha y la hora del evento
    eventoTime.tm_year = ev.año - 1900; // Se le resta al 1900 al año por la estructura "tm" si ingresa 2023 se le resta 1900 y queda 123 y así lo lee
    eventoTime.tm_mon = ev.mes - 1;
    eventoTime.tm_mday = ev.dia;
    eventoTime.tm_hour = ev.hora;
    eventoTime.tm_min = ev.minuto;
    eventoTime.tm_sec = 0;

    time_t eventoTiempo = mktime(&eventoTime);// La estructura eventoTime se convierte en un valor de tiempo (time_t) que representa la fecha y hora del evento seleccionado
    double segundosRestantes = difftime(eventoTiempo, ahora); // Esto calcula la diferencia de segundos entre el tiempo del evento "eventoTiempo" y el tiempo actual "ahora" que dice cuántos segundos faltan para que ocurra el evento con el difftime

    if (segundosRestantes < 0) {// Verifica si los segundos son menores a cero
        std::cout << "El evento \"" << ev.nombres << "\" ya ha pasado" << std::endl;
    } else { //variables con los segundos de un minuto, hora,dias,meses,años
        const int segundosEnMinuto = 60;
        const int segundosEnHora = 3600;
        const int segundosEnDia = 86400;
        const int segundosEnMes = 2592000; // teniendo en cuanta que un mes tiene 30.44 dias
        const int segundosEnAño = 31536000; // teniendo en cuenta que un año tiene 365.25 dias

        int añosRestantes = static_cast<int>(segundosRestantes / segundosEnAño); //la operacion aqui declaramos un entero añosRestantes que es igual a segundosRestantes que esta variable esta en double y que almacena la fecha ingresada en segundos 
        segundosRestantes -= añosRestantes * segundosEnAño;                      //se divide en segundos en años que lo declaramos luego años restantes es igual menos segundos restantes multiplicado por segundos en años y lo mismo en las demas lineas

        int mesesRestantes = static_cast<int>(segundosRestantes / segundosEnMes); // Divide segundos en meses
        segundosRestantes -= mesesRestantes * segundosEnMes;

        int diasRestantes = static_cast<int>(segundosRestantes / segundosEnDia); // Divide segundos en días
        segundosRestantes -= diasRestantes * segundosEnDia;

        int horasRestantes = static_cast<int>(segundosRestantes / segundosEnHora); // Divide segundos en horas
        segundosRestantes -= horasRestantes * segundosEnHora;

        int minutosRestantes = static_cast<int>(segundosRestantes / segundosEnMinuto); // Convierte segundos en minutos

        std::cout << "Tiempo restante para el evento \"" << ev.nombres << "\":" << std::endl;
        if (añosRestantes > 0) {//agara la variable ya convertidas en años y la muestra junto con las demas lineas de este if 
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

//funcion para mostrar eventos a 30 dias
void mostrarEventosProximos30Dias(const std::vector<evento>& agenda) {
    std::vector<evento> eventosProximos30Dias;

    // Obtener la fecha actual
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(today);

    std::tm localTime = *std::localtime(&currentTime);
    int todayDay = localTime.tm_mday;
    int todayMonth = localTime.tm_mon + 1; // tm_mon va de 0 a 11, por lo que sumamos 1 para obtener el mes real
    int todayYear = localTime.tm_year + 1900; // tm_year cuenta desde 1900, por lo que sumamos 1900

    for (const evento& ev : agenda) {
        // Verificar si el evento está dentro de los próximos 30 días
        if (ev.año == todayYear && ev.mes == todayMonth) {
            if (ev.dia >= todayDay && ev.dia - todayDay <= 30) {
                eventosProximos30Dias.push_back(ev);
            }
        }
    }

    if (!eventosProximos30Dias.empty()) {
        // Ordenar los eventos por fecha
        std::sort(eventosProximos30Dias.begin(), eventosProximos30Dias.end(), [](const evento& a, const evento& b) {
            // Comparar las fechas
            if (a.año != b.año) {
                return a.año < b.año;
            } else if (a.mes != b.mes) {
                return a.mes < b.mes;
            } else {
                return a.dia < b.dia;
            }
        });

        std::cout << "Eventos de los próximos 30 días:" << std::endl;
        for (const evento& ev : eventosProximos30Dias) {
            std::cout << "Evento: " << ev.nombres << " Fecha: " << ev.dia << "/" << ev.mes << "/" << ev.año
                      << " Hora: " << ev.hora << ":" << ev.minuto << std::endl;
        }
    } else {
        std::cout << "No hay eventos en los próximos 30 días." << std::endl;
    }
}

int main() {
    std::vector<evento> agenda; // Declaración del vector llamado agenda para guardar los eventos

    while (true) {
        std::cout << "MENU DE OPCIONES" << std::endl;
        std::cout << "1. Agregar un evento" << std::endl;
        std::cout << "2. Mostrar todos los eventos" << std::endl;
        std::cout << "3. Mostrar tiempo para el evento" << std::endl;
        std::cout << "4. Mostrar los eventos proximos a 30 dias" << std::endl;
        std::cout << "5. Eliminar un evento" << std::endl; // Opción para eliminar eventos
        std::cout << "6. Editar un evento" << std::endl;   // Opción para editar eventos
        std::cout << "7. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";

        int opc = obtenerEnteroValido();

        evento evento; // Declaración de una variable evento para guardar temporalmente los datos de un evento

        switch (opc) {
            case 1: // Agregar eventos
                std::cout << "Ingrese el nombre del evento: ";
                std::getline(std::cin, evento.nombres);

                obtenerFechaValida(evento.dia, evento.mes, evento.año);
                obtenerHoraValida(evento.hora, evento.minuto);

                agenda.push_back(evento); // Lo agrega al vector
                break;
            case 2: // Mostrar eventos
                if (!agenda.empty()) {
                    std::cout << "Lista de Eventos:" << std::endl;
                    for (int i = 0; i < agenda.size(); i++) { // agenda.size muestra el tamaño del vector 
                        std::cout << "Evento " << i + 1 << ": " << agenda[i].nombres << " Fecha: " << agenda[i].dia << "/" << agenda[i].mes << "/" << agenda[i].año//muestra todos los datos ingresador del evento
                                  << " Hora: " << agenda[i].hora << ":" << agenda[i].minuto <<std::endl;
                    }
                } else {
                    std::cout << "No hay eventos para mostrar" << std::endl;
                }
                break;
            case 3: // Calcular tiempo para el evento
                if (!agenda.empty()) {
                    std::cout << "Lista de Eventos:" << std::endl;
                    for (int i = 0; i < agenda.size(); i++) { // agenda.size muestra el tamaño del vector 
                        std::cout << "Evento " << i + 1 << ": " << agenda[i].nombres << " Fecha: " << agenda[i].dia << "/" << agenda[i].mes << "/" << agenda[i].año//muestra todos los datos ingresador del evento
                                  << " Hora: " << agenda[i].hora << ":" << agenda[i].minuto <<std::endl;
                    }
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
            case 4:
                if (!agenda.empty()) {
                    mostrarEventosProximos30Dias(agenda);
                }else {
                    std::cout<< "No hay eventos prximos a 30 dias" << std::endl; 
                }
                break;
            case 5: // Eliminar evento
                if (!agenda.empty()) {
                    std::cout << "Lista de Eventos:" << std::endl;
                    for (int i = 0; i < agenda.size(); i++) { // agenda.size muestra el tamaño del vector 
                        std::cout << "Evento " << i + 1 << ": " << agenda[i].nombres << " Fecha: " << agenda[i].dia << "/" << agenda[i].mes << "/" << agenda[i].año//muestra todos los datos ingresador del evento
                                  << " Hora: " << agenda[i].hora << ":" << agenda[i].minuto <<std::endl;
                    }
                    std::cout << "Ingrese el número de evento que desea eliminar: ";
                    int numEvento = obtenerEnteroValido();

                    if (numEvento >= 1 && numEvento <= agenda.size()) {
                        // Elimina el evento seleccionado del vector
                        agenda.erase(agenda.begin() + numEvento - 1); // elimina la agenda seleccionada por ejemplo selecciono 5 pone agenda.borra inicia desde el comienzo le suma el 5 seleccionada y elimina el evento que esta en el vector 
                        std::cout << "Evento eliminado con éxito" << std::endl;
                    } else {
                        std::cout << "Número de evento no válido" << std::endl;
                    }
                } else {
                    std::cout << "No hay eventos para eliminar" << std::endl;
                }
                break;
            case 6: // Editar evento
                if (!agenda.empty()) {
                    std::cout << "Lista de Eventos:" << std::endl;
                    for (int i = 0; i < agenda.size(); i++) { // agenda.size muestra el tamaño del vector 
                        std::cout << "Evento " << i + 1 << ": " << agenda[i].nombres << " Fecha: " << agenda[i].dia << "/" << agenda[i].mes << "/" << agenda[i].año//muestra todos los datos ingresador del evento
                                  << " Hora: " << agenda[i].hora << ":" << agenda[i].minuto <<std::endl;
                    }
                    std::cout << "Ingrese el número de evento que desea editar: ";
                    int numEvento = obtenerEnteroValido();

                    if (numEvento >= 1 && numEvento <= agenda.size()) {
                        evento = agenda[numEvento - 1]; // Obtenemos una referencia al evento que se va a editar

                        std::cout << "Ingrese el nuevo nombre del evento: ";
                        std::cin.ignore(); // Para consumir la nueva línea en el búfer.
                        std::getline(std::cin, evento.nombres);

                        obtenerFechaValida(evento.dia, evento.mes, evento.año);
                        obtenerHoraValida(evento.hora, evento.minuto);
                    } else {
                        std::cout << "No hay eventos para editar" << std::endl;
                    }
                }
                break;
                case 7: // Salir del programa
                    std::cout << "Saliendo del programa" << std::endl;
                    return 0;
                default:
                    std::cout << "Opción no válida. Por favor, seleccione un número válido" << std::endl;
                    
            }//fin del switch case
            }
    return 0;
}
    