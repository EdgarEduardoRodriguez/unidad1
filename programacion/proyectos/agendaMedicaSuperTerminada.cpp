#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <limits>
#include <algorithm> // Agregar esta librería para usar std::sort
#include <chrono> 

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
                        // Verificar si el consultorio ya está ocupado
                        if (consultoriosDoctores[numDoctor - 1][1].empty()) {
                            std::cout << "Seleccione el consultorio (1-10) al que desea asignar al doctor: ";
                            int numConsultorio = obtenerEnteroValido();
            
                            bool consultorioDisponible = true;
                            for (const auto& doctor : consultoriosDoctores) {
                                if (doctor[1] == std::to_string(numConsultorio)) {
                                    consultorioDisponible = false;
                                    break;
                                }
                            }
            
                            if (numConsultorio >= 1 && numConsultorio <= 10 && consultorioDisponible) {
                                consultoriosDoctores[numDoctor - 1][1] = std::to_string(numConsultorio);
                                std::cout << "Doctor \"" << consultoriosDoctores[numDoctor - 1][0]
                                          << "\" asignado al consultorio " << numConsultorio << " con éxito." << std::endl;
                            } else {
                                std::cout << "El consultorio seleccionado ya tiene un doctor asignado o no es válido." << std::endl;
                            }
                        } else {
                            std::cout << "El doctor seleccionado ya tiene un consultorio asignado." << std::endl;
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
//funcion por si una cita interfiere
bool eventoInterfiere(const evento& nuevaCita, const std::vector<evento>& agenda) {
    for (const evento& cita : agenda) {
        if (&cita != &nuevaCita) { // Compara si la cita no es la misma que se está editando
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
    }
    return false; // No hay interferencia
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
        std::cout << i + 1 << ". " << consultoriosDoctores[i][0] << " - Consultorio: " << consultoriosDoctores[i][1] << std::endl;
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

    while (eventoInterfiere(nuevoEvento, agenda)) {
        std::cout << "La cita coincide con otra en el mismo consultorio." << std::endl;
        std::cout << "¿Desea cambiar la fecha, el consultorio o cancelar la operación?" << std::endl;
        std::cout << "1. Cambiar la fecha" << std::endl;
        std::cout << "2. Cambiar el consultorio" << std::endl;
        std::cout << "3. Cancelar" << std::endl;
        std::cout << "Seleccione una opción: ";
        
        int cambio = obtenerEnteroValido();

        switch (cambio) {
            case 1: // Cambiar la fecha
                obtenerFechaValida(nuevoEvento.dia, nuevoEvento.mes, nuevoEvento.año);
                break;
            case 2: // Cambiar el consultorio
                std::cout << "Consultorios existentes:" << std::endl;
                for (size_t i = 0; i < consultoriosDoctores.size(); ++i) {
                    std::cout << i + 1 << ". " << consultoriosDoctores[i][0] << " - Consultorio: " << consultoriosDoctores[i][1] << std::endl;
                }
                std::cout << "Seleccione el número del consultorio al que desea asignar al paciente: ";
                numConsultorio = obtenerEnteroValido();
                if (numConsultorio >= 1 && numConsultorio <= consultoriosDoctores.size()) {
                    nuevoEvento.consultorio = numConsultorio;
                } else {
                    std::cout << "Número de consultorio no válido." << std::endl;
                    return;
                }
                break;
            case 3: // Cancelar la operación
                std::cout << "Operación cancelada." << std::endl;
                return;
            default:
                std::cout << "Opción no válida. Por favor, seleccione un número válido." << std::endl;
        }
    }

    agenda.push_back(nuevoEvento);
    std::cout << "Evento agregado con éxito." << std::endl;
}
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
            std::cout << "Nombre del Paciente: " << ev.nombres << " Fecha: " << ev.dia << "/" << ev.mes << "/" << ev.año
                      << " Hora: " << ev.hora << ":" << ev.minuto << " - " << ev.horaFin << ":" << ev.minutoFin << std::endl;
        }
    } else {
        std::cout << "No hay eventos en los próximos 30 días." << std::endl;
    }
}
void editarEvento(std::vector<evento>& agenda, const std::vector<std::vector<std::string>>& consultoriosDoctores) {
    if (agenda.empty()) {
        std::cout << "No hay eventos para editar." << std::endl;
        return;
    }

    std::cout << "Seleccione el número de la cita que desea editar:" << std::endl;
    for (int i = 0; i < agenda.size(); i++) {
        std::cout << i + 1 << ". Nombre: " << agenda[i].nombres << " - Fecha: " << agenda[i].dia << "/" << agenda[i].mes << "/" << agenda[i].año
                  << " - Hora: " << agenda[i].hora << ":" << agenda[i].minuto << " - Doctor: ";
        int consultorioEvento = agenda[i].consultorio;
        std::string nombreDoctor = (consultorioEvento >= 1 && consultorioEvento <= consultoriosDoctores.size())
                                      ? consultoriosDoctores[consultorioEvento - 1][0]
                                      : "No asignado";
        std::cout << nombreDoctor << std::endl;
    }

    int numCita;
    std::cout << "Ingrese el número de la cita que desea editar: ";
    std::cin >> numCita;

    if (numCita >= 1 && numCita <= agenda.size()) {
        evento& citaAEditar = agenda[numCita - 1];

        std::cout << "La cita seleccionada se editará a continuación." << std::endl;

        std::cout << "Ingrese el nuevo nombre del paciente: ";
        std::cin.ignore();
        std::getline(std::cin, citaAEditar.nombres);

        std::cout << "Consultorios existentes:" << std::endl;
        for (size_t i = 0; i < consultoriosDoctores.size(); ++i) {
            std::cout << i + 1 << ". " << consultoriosDoctores[i][0] << " - Consultorio: " << consultoriosDoctores[i][1] << std::endl;
        }

        std::cout << "Seleccione el número del consultorio al que desea asignar al paciente: ";
        int numConsultorio;
        std::cin >> numConsultorio;

        if (numConsultorio >= 1 && numConsultorio <= consultoriosDoctores.size()) {
            citaAEditar.consultorio = numConsultorio;
        } else {
            std::cout << "Número de consultorio no válido." << std::endl;
            return;
        }
        
        obtenerFechaValida(citaAEditar.dia, citaAEditar.mes, citaAEditar.año);
        obtenerHoraValida(citaAEditar.hora, citaAEditar.minuto);
        obtenerHoraValidaFinal(citaAEditar.horaFin, citaAEditar.minutoFin);
        

        // Lógica para obtener y validar la nueva fecha y hora de la cita

        while (eventoInterfiere(citaAEditar, agenda)) {
            std::cout << "La cita coincide con otra en el mismo consultorio." << std::endl;
            std::cout << "¿Desea cambiar la fecha, el consultorio o cancelar la operación?" << std::endl;
            std::cout << "1. Cambiar la fecha" << std::endl;
            std::cout << "2. Cambiar el consultorio" << std::endl;
            std::cout << "3. Cancelar" << std::endl;
            std::cout << "Seleccione una opción: ";

            int cambio;
            std::cin >> cambio;

            switch (cambio) {
                case 1: // Cambiar la fecha
                    obtenerFechaValida(citaAEditar.dia, citaAEditar.mes, citaAEditar.año);
                    // Aquí podrías agregar la lógica necesaria para cambiar la fecha
                    // y luego volver a verificar si hay interferencias.
                    break;
                case 2: // Cambiar el consultorio
                    std::cout << "Consultorios existentes:" << std::endl;
                    for (size_t i = 0; i < consultoriosDoctores.size(); ++i) {
                        std::cout << i + 1 << ". " << consultoriosDoctores[i][0] << " - Consultorio: " << consultoriosDoctores[i][1] << std::endl;
                    }
                    std::cout << "Seleccione el número del consultorio al que desea asignar al paciente: ";
                    int numConsultorio;
                    std::cin >> numConsultorio;
                    if (numConsultorio >= 1 && numConsultorio <= consultoriosDoctores.size()) {
                        citaAEditar.consultorio = numConsultorio;
                        // Aquí podrías agregar la lógica para cambiar el consultorio
                        // y luego volver a verificar si hay interferencias.
                    } else {
                        std::cout << "Número de consultorio no válido." << std::endl;
                        return;
                    }
                    break;
                case 3: // Cancelar la operación
                    std::cout << "Operación cancelada." << std::endl;
                    return;
                default:
                    std::cout << "Opción no válida. Por favor, seleccione un número válido." << std::endl;
            }

        }

        std::cout << "Evento editado con éxito." << std::endl;
    } else {
        std::cout << "Número de cita no válido." << std::endl;
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
            
                        std::cout << "Cita " << i + 1 << " Nombre del Paciente: " << agenda[i].nombres << " Doctor: " << consultoriosDoctores[i][0] << " - Consultorio: " << consultoriosDoctores[i][1] 
                                  << " Fecha: " << agenda[i].dia << "/" << agenda[i].mes << "/" << agenda[i].año
                                  << " a las " << agenda[i].hora << ":" << agenda[i].minuto << " hasta " << agenda[i].horaFin << ":" << agenda[i].minutoFin << std::endl;
                    }
                } else {
                    std::cout << "No hay citas para mostrar" << std::endl;
                }
                break;
            case 4: // Mostrar eventos dentro del próximo mes, ordenados por cercanía
                mostrarEventosProximos30Dias(agenda);
                break;
            case 5: // Eliminar evento
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
                editarEvento(agenda, consultoriosDoctores);
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