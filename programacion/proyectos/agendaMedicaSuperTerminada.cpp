#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <limits>

// Definición de la estructura para representar un evento
struct evento {
    std::string nombres;
    int dia, mes, año, hora, minuto, diaFin, mesFin, añoFin, horaFin, minutoFin;
    int consultorio;
    std::string doctores;
    
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

void gestionarDoctores(std::vector<std::vector<std::string>>&consultoriosDoctores) {
    std::string nuevoDoctor;;
    while (true) {
        std::cout << "MENÚ DE GESTIÓN DE DOCTORES" << std::endl;
        std::cout << "1. Agregar Doctor" << std::endl;
        std::cout << "2. Editar Doctor" << std::endl;
        std::cout << "3. Asignar Doctor a Consultorio" << std::endl;
        std::cout << "4. Eliminar Doctor" << std::endl;
        std::cout << "5. Mostrar Doctores y Consultorios" << std::endl;
        std::cout << "6. Volver al menú principal" << std::endl;
        std::cout << "Seleccione una opción: ";

        int opc = obtenerEnteroValido();

        switch (opc) {
            case 1: // Agregar Doctor
                std::cout << "Ingrese el nombre del nuevo doctor: ";
                std::cin.ignore();
                std::getline(std::cin, nuevoDoctor);
                consultoriosDoctores.push_back({ nuevoDoctor, "" });
                std::cout << "Doctor agregado con éxito." << std::endl;
                break;

            case 2: // Editar Doctor
                if (!consultoriosDoctores.empty()) {
                    std::cout << "Doctores registrados:" << std::endl;
                    for (int i = 0; i < consultoriosDoctores.size(); i++) {
                        std::cout << i + 1 << ". " << consultoriosDoctores[i][0] << std::endl;
                    }

                    std::cout << "Ingrese el número del doctor que desea editar: ";
                    int numDoctor = obtenerEnteroValido();

                    if (numDoctor >= 1 && numDoctor <= consultoriosDoctores.size()) {
                        std::cout << "Ingrese el nuevo nombre del doctor: ";
                        std::cin.ignore();
                        std::getline(std::cin, consultoriosDoctores[numDoctor - 1][0]);
                        std::cout << "Doctor editado con éxito." << std::endl;
                    } else {
                        std::cout << "Número de doctor no válido." << std::endl;
                    }
                } else {
                    std::cout << "No hay doctores para editar." << std::endl;
                }
                break;

            case 3: // Asignar Doctor a Consultorio
                if (!consultoriosDoctores.empty()) {
                    std::cout << "Doctores registrados:" << std::endl;
                    for (int i = 0; i < consultoriosDoctores.size(); i++) {
                        std::cout << i + 1 << ". " << consultoriosDoctores[i][0] << std::endl;
                    }

                    std::cout << "Ingrese el número del doctor al que desea asignar un consultorio: ";
                    int numDoctor = obtenerEnteroValido();

                    if (numDoctor >= 1 && numDoctor <= consultoriosDoctores.size()) {
                        std::cout << "Seleccione el consultorio (1-10) al que desea asignar al doctor: ";
                        int numConsultorio = obtenerEnteroValido();

                        if (numConsultorio >= 1 && numConsultorio <= 10) {
                            consultoriosDoctores[numDoctor - 1][1] = std::to_string(numConsultorio);
                            std::cout << "Doctor \"" << consultoriosDoctores[numDoctor - 1][0]
                                << "\" asignado al consultorio " << numConsultorio << " con éxito." << std::endl;
                        } else {
                            std::cout << "Número de consultorio no válido." << std::endl;
                        }
                    } else {
                        std::cout << "Número de doctor no válido." << std::endl;
                    }
                } else {
                    std::cout << "No hay doctores para asignar a consultorios." << std::endl;
                }
                break;

            case 4: // Eliminar Doctor
                if (!consultoriosDoctores.empty()) {
                    std::cout << "Doctores registrados:" << std::endl;
                    for (int i = 0; i < consultoriosDoctores.size(); i++) {
                        std::cout << i + 1 << ". " << consultoriosDoctores[i][0] << std::endl;
                    }

                    std::cout << "Ingrese el número del doctor que desea eliminar: ";
                    int numDoctor = obtenerEnteroValido();

                    if (numDoctor >= 1 && numDoctor <= consultoriosDoctores.size()) {
                        std::string doctorEliminado = consultoriosDoctores[numDoctor - 1][0];
                        consultoriosDoctores.erase(consultoriosDoctores.begin() + numDoctor - 1);
                        std::cout << "Doctor \"" << doctorEliminado << "\" eliminado con éxito." << std::endl;
                    } else {
                        std::cout << "Número de doctor no válido." << std::endl;
                    }
                } else {
                    std::cout << "No hay doctores para eliminar." << std::endl;
                }
                break;

            case 5: // Mostrar Doctores y Consultorios
                if (!consultoriosDoctores.empty()) {
                    std::cout << "Doctores y sus consultorios:" << std::endl;
                    for (int i = 0; i < consultoriosDoctores.size(); i++) {
                        std::cout << i + 1 << ". " << consultoriosDoctores[i][0] << " - Consultorio: " << consultoriosDoctores[i][1] << std::endl;
                    }
                } else {
                    std::cout << "No hay doctores registrados." << std::endl;
                }
                break;
            case 6: // Volver al menú principal
                return;

            default:
                std::cout << "Opción no válida. Por favor, seleccione un número válido" << std::endl;
        }
    }
}

bool hayDoctores(const std::vector<std::vector<std::string>>& consultoriosDoctores) {
    for (const std::vector<std::string>& doctorInfo : consultoriosDoctores) {
        if (!doctorInfo[1].empty()) {
            return true;
        }
    }
    return false;
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

void obtenerHoraValidaFinal(int& hora, int& minuto) {//funcion para preguntar la hora y verificar si esta bien
    while (true) {
        std::string horaStr;
        std::cout << "Ingrese la hora en que finaliza la cita (HH:MM): ";
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
// Función para verificar si una nueva cita interfiere con otras citas en el mismo consultorio
bool eventoInterfiere(const evento& nuevaCita, const std::vector<evento>& agenda) {
    for (const evento& cita : agenda) {
        if (cita.consultorio == nuevaCita.consultorio &&
            ((nuevaCita.año == cita.año && nuevaCita.mes == cita.mes && nuevaCita.dia == cita.dia &&
                nuevaCita.hora < cita.horaFin && nuevaCita.horaFin > cita.hora) ||
             (nuevaCita.año == cita.año && nuevaCita.mes == cita.mes && nuevaCita.dia == cita.dia &&
                nuevaCita.hora == cita.hora && nuevaCita.minuto == cita.minuto) ||
             (nuevaCita.año == cita.año && nuevaCita.mes == cita.mes && nuevaCita.dia == cita.dia &&
                nuevaCita.horaFin == cita.horaFin && nuevaCita.minutoFin == cita.minutoFin))) {
            return true; // Hay interferencia
        }
    }
    return false; // No hay interferencia
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
void agregarEvento(std::vector<evento>& agenda, const std::vector<std::vector<std::string>>& consultoriosDoctores) {
    if (consultoriosDoctores.empty()) {
        std::cout << "No se pueden agregar eventos hasta que haya al menos un doctor asignado a un consultorio." << std::endl;
        return;
    }

    evento nuevoEvento;

    std::cout << "Ingrese el nombre del paciente: ";
    std::cin.ignore();
    std::getline(std::cin, nuevoEvento.nombres);

    std::cout << "Consultorios existentes:" << std::endl;
    for (size_t i = 0; i < consultoriosDoctores.size(); ++i) {
        std::cout << i + 1 << ". Consultorio " << i + 1 << " - Doctor: " << consultoriosDoctores[i][0] << std::endl;
    }

    std::cout << "Seleccione el número del consultorio al que desea asignar al paciente: ";
    int numConsultorio = obtenerEnteroValido();

    if (numConsultorio >= 1 && numConsultorio <= consultoriosDoctores.size()) {
        nuevoEvento.consultorio = numConsultorio;
    } else {
        std::cout << "Número de consultorio no válido." << std::endl;
        return;
    }

    obtenerFechaValida(nuevoEvento.dia, nuevoEvento.mes, nuevoEvento.año);
    obtenerHoraValida(nuevoEvento.hora, nuevoEvento.minuto);
    obtenerHoraValidaFinal(nuevoEvento.horaFin, nuevoEvento.minutoFin);

    if (eventoInterfiere(nuevoEvento, agenda)) {
        std::cout << "La cita coincide con otra en el mismo consultorio. Por favor, elija otro horario." << std::endl;
    } else {
        agenda.push_back(nuevoEvento);
        std::cout << "Evento agregado con éxito." << std::endl;
    }
}

int main() {
    std::vector<evento> agenda; // Declaración del vector llamado agenda para guardar los eventos
    std::vector<std::vector<std::string>> consultoriosDoctores; // Matriz de asociación entre doctores y consultorios
    bool hayConsultoriosConDoctores = false;
    while (true) {
        std::cout << "MENU DE OPCIONES" << std::endl;
        std::cout << "1. Gestión de Doctores" << std::endl;
        std::cout << "2. Agregar un cita" << std::endl;
        std::cout << "3. Mostrar todos los eventos" << std::endl;
        std::cout << "4. Mostrar tiempo para el evento" << std::endl;
        std::cout << "5. Eliminar un evento" << std::endl; // Opción para eliminar eventos
        std::cout << "6. Editar un evento" << std::endl;   // Opción para editar eventos
        std::cout << "7. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";

        int opc = obtenerEnteroValido();

        evento evento; // Declaración de una variable evento para guardar temporalmente los datos de un evento

        switch (opc) {
            case 1: // gestión de Doctores
                gestionarDoctores(consultoriosDoctores);
                break;
            case 2:
                agregarEvento(agenda, consultoriosDoctores);
                break;
            case 3: // Mostrar eventos
                if (!hayConsultoriosConDoctores) {
                    std::cout << "No se pueden editar eventos hasta que haya al menos un doctor asignado a un consultorio." << std::endl;
                    break;
                }
                if (!agenda.empty()) {
                    std::cout << "Lista de Eventos:" << std::endl;
                    for (int i = 0; i < agenda.size(); i++) {
                        int consultorioEvento = agenda[i].consultorio; // Obtiene el número del consultorio asignado a este evento
                
                        // Encuentra el nombre del doctor asignado al consultorio
                        std::string nombreDoctor;
                        if (consultorioEvento >= 1 && consultorioEvento <= consultoriosDoctores.size()) {
                            nombreDoctor = consultoriosDoctores[consultorioEvento - 1][0];
                        } else {
                            nombreDoctor = "No asignado";
                        }
            
                        std::cout << "Evento " << i + 1 << ": " << agenda[i].nombres << " Doctor: " << nombreDoctor
                                  << " Consultio: " << agenda[i].consultorio << " Fecha: " << agenda[i].dia << "/" << agenda[i].mes << "/" << agenda[i].año
                                  << " Hora: " << agenda[i].hora << ":" << agenda[i].minuto << " Hora de finalización de la cita " << agenda[i].horaFin << ":" << agenda[i].minutoFin << std::endl;
                    }
                } else {
                    std::cout << "No hay eventos para mostrar" << std::endl;
                }
                break;
            case 4: // Calcular tiempo para el evento
                if (!hayConsultoriosConDoctores) {
                    std::cout << "No se pueden editar eventos hasta que haya al menos un doctor asignado a un consultorio." << std::endl;
                    break;
                }
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
            case 5: // Eliminar evento
                if (!hayConsultoriosConDoctores) {
                    std::cout << "No se pueden editar eventos hasta que haya al menos un doctor asignado a un consultorio." << std::endl;
                    break;
                }
                if (!agenda.empty()) {
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
                if (!hayConsultoriosConDoctores) {
                    std::cout << "No se pueden editar eventos hasta que haya al menos un doctor asignado a un consultorio." << std::endl;
                    break;
                }
                if (!agenda.empty()) {
                    std::cout << "Ingrese el número de evento que desea editar: ";
                    int numEvento = obtenerEnteroValido();
                    if (numEvento >= 1 && numEvento <= agenda.size()) {
                        evento = agenda[numEvento - 1]; // Obtenemos una referencia al evento que se va a editar

                        std::cout << "Ingrese el nuevo nombre del evento: ";
                        std::cin.ignore(); // Para consumir la nueva línea en el búfer.
                        std::getline(std::cin, evento.nombres);

                        std::cout << "Ingrese el nombre del doctor: ";
                        std::cin.ignore();
                        std::getline(std::cin, evento.doctores);

                        std::cout << "Evento editado con éxito" << std::endl;
                    } else {
                        std::cout << "Número de evento no válido" << std::endl;
                    }
                } else {
                    std::cout << "No hay eventos para editar" << std::endl;
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