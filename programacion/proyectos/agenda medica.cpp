#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <limits>
#include <algorithm> // Agregar esta librería para usar std::sort
#include <chrono> 
#include <sstream>
#include <fstream>

// Definición de la estructura para representar un evento
struct HorarioTrabajo {
    int horaEntrada;
    int minutoEntrada;
    int horaSalida;
    int minutoSalida;
};
// Definicion de estrctura para cita
struct evento {
    std::string nombres;
    int dia, mes, año, hora, minuto, horaFin, minutoFin;
    int consultorio;
    std::string doctores;
    int horaEntrada;
    int horaSalida;
    std::string nombreDoctor;  // Agregar esta línea
};

// Variables globales para la fecha actual
std::time_t t = std::time(0);
std::tm* now = std::localtime(&t);
int añoActual = now->tm_year + 1900;
int mesActual = now->tm_mon + 1;
int diaActual = now->tm_mday;

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
// Función para escribir doctores en el archivo
void escribirDoctoresEnArchivo(const std::vector<std::vector<std::string>>& doctores, const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        for (const auto& doctor : doctores) {
            // Formato: Nombre,Consultorio,DiasTrabajo,HoraEntrada,MinutoEntrada,HoraSalida,MinutoSalida
            archivo << doctor[0] << ","
                    << doctor[1] << ","
                    << doctor[2] << ","
                    << doctor[3] << ","
                    << doctor[4] << "," 
                    << doctor[5] << ","
                    << doctor[6] << std::endl;
        }

        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
    }
}

// Función para leer doctores desde el archivo
void leerDoctoresDeArchivo(std::vector<std::vector<std::string>>& doctores, const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        doctores.clear(); // Limpiar el vector antes de cargar nuevos datos

        std::string linea;
        while (std::getline(archivo, linea)) {// este bucle va leyendo cada linea y lo almacena en la variable linea
            std::istringstream ss(linea);// esto se usa para dividir la línea en elementos separados por comas
            std::vector<std::string> doctor;// creacion del elemnto doctor para guardar los elmentos en una linea y una variable
            std::string elemento;// esto para guardar cada elemento mientras se lee

            while (std::getline(ss, elemento, ',')) { // este bucle while interno, se usa std::getline para leer cada elemento separado por comas de la línea 
                doctor.push_back(elemento);// y se agrega al vector doctor
            }

            doctores.push_back(doctor);
        }

        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
    }
}

// Función para escribir eventos en el archivo
void escribirEventosEnArchivo(const std::vector<evento>& eventos, const std::vector<std::vector<std::string>>& consultoriosDoctores, const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        for (const auto& evento : eventos) {
            // Formato: Nombres,Dia,Mes,Año,Hora,Minuto,HoraFin,MinutoFin,Consultorio,NombreDoctor
            archivo << evento.nombres << ","
                    << evento.dia << ","
                    << evento.mes << ","
                    << evento.año << ","
                    << evento.hora << ","
                    << evento.minuto << ","
                    << evento.horaFin << ","
                    << evento.minutoFin << ","
                    << " - Consultorio: " << consultoriosDoctores[evento.consultorio - 1][1] << std::endl;
        }

        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
    }
}




// Función para leer eventos desde el archivo
void leerEventosDeArchivo(std::vector<evento>& eventos, const std::vector<std::vector<std::string>>& consultoriosDoctores, const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        eventos.clear(); // Limpiar el vector antes de cargar nuevos datos

        std::string linea;
        while (std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            evento nuevoEvento;

            // Leer datos del evento desde la línea
            std::string elemento;

            // Nombre del paciente
            std::getline(ss, nuevoEvento.nombres, ',');

            // Día, mes, año
            std::getline(ss, elemento, ',');
            nuevoEvento.dia = std::stoi(elemento);
            std::getline(ss, elemento, ',');
            nuevoEvento.mes = std::stoi(elemento);
            std::getline(ss, elemento, ',');
            nuevoEvento.año = std::stoi(elemento);

            // Hora, minuto
            std::getline(ss, elemento, ',');
            nuevoEvento.hora = std::stoi(elemento);
            std::getline(ss, elemento, ',');
            nuevoEvento.minuto = std::stoi(elemento);

            // HoraFin, minutoFin
            std::getline(ss, elemento, ',');
            nuevoEvento.horaFin = std::stoi(elemento);
            std::getline(ss, elemento, ',');
            nuevoEvento.minutoFin = std::stoi(elemento);

            // Consultorio
            std::getline(ss, elemento, '-');
            std::cout << "DEBUG: Elemento después del guion: " << elemento << std::endl;
            std::getline(ss, elemento, ':');
            std::cout << "DEBUG: Elemento después de los dos puntos: " << elemento << std::endl;


            eventos.push_back(nuevoEvento);
        }

        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
    }
}



// Funcion para obtener dias de trabajo
std::string obtenerDiasTrabajo() {
    std::string diasTrabajo;

    std::vector<std::string> diasSemana = { "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado", "Domingo" };

    for (const auto& dia : diasSemana) {
        char respuesta;

        while (true) {
            std::cout << "¿Trabaja los " << dia << "? (s/n): ";
            std::cin >> respuesta;

            // Verificar si la entrada es válida y si es 's' o 'n'
            if (std::cin.fail() || (std::cin.peek() != '\n') || (respuesta != 's' && respuesta != 'S' && respuesta != 'n' && respuesta != 'N')) {
                std::cout << "Respuesta no válida. Ingrese 's' o 'n'." << std::endl;

                // Limpiar el estado de error y el búfer del cin
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                // Limpiar el búfer del cin en caso de entrada adicional
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;  // Salir del bucle si la entrada es válida
            }
        }

        if (respuesta == 's' || respuesta == 'S') {
            diasTrabajo += dia + " ";
        }
    }

    return diasTrabajo;
}


bool validarDiasTrabajo(const std::string& diasTrabajo) {
    int contadorDias = 0;
    for (char c : diasTrabajo) {
        if (c == ' ') {
            contadorDias++;
        }
    }
    return contadorDias >= 2;
}

bool esFormatoHoraValido(const std::string& horaStr) {
    // Verifica si la cadena tiene el formato correcto (HH:MM)
    return horaStr.size() == 5 && horaStr[2] == ':' &&
           std::isdigit(horaStr[0]) && std::isdigit(horaStr[1]) &&
           std::isdigit(horaStr[3]) && std::isdigit(horaStr[4]);
}

HorarioTrabajo obtenerHorarioTrabajo() {
    HorarioTrabajo horario;
    char separator;

    // Loop hasta que se ingrese un formato válido
    while (true) {
        std::cout << "Ingrese la hora de entrada (formato 24 horas, por ejemplo, 12:00): ";
        std::string entrada;
        std::cin >> entrada;

        if (esFormatoHoraValido(entrada)) {
            std::stringstream ss(entrada);
            ss >> horario.horaEntrada >> separator >> horario.minutoEntrada;

            // Verificar si la entrada es válida y si el separador es ':'
            if (ss.fail() || separator != ':' || ss.peek() != EOF) {
                std::cout << "Formato de entrada inválido. Inténtelo de nuevo.\n";
            } else {
                break;  // Salir del bucle si la entrada es válida
            }
        } else {
            std::cout << "Formato de hora no válido. Use el formato HH:MM (por ejemplo, 13:30)." << std::endl;
            // Limpiar el búfer del cin en caso de entrada adicional
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // Loop hasta que se ingrese un formato válido
    while (true) {
        std::cout << "Ingrese la hora de salida (formato 24 horas, por ejemplo, 18:00): ";
        std::string salida;
        std::cin >> salida;

        if (esFormatoHoraValido(salida)) {
            std::stringstream ss(salida);
            ss >> horario.horaSalida >> separator >> horario.minutoSalida;

            // Verificar si la entrada es válida y si el separador es ':'
            if (ss.fail() || separator != ':' || ss.peek() != EOF) {
                std::cout << "Formato de entrada inválido. Inténtelo de nuevo.\n";
            } else if ((horario.horaSalida - horario.horaEntrada) * 60 + (horario.minutoSalida - horario.minutoEntrada) < 300) {
                std::cout << "El doctor debe trabajar al menos 5 horas al día. Inténtelo de nuevo.\n";
            } else {
                break;  // Salir del bucle si la entrada es válida y cumple con el requisito de horas mínimas
            }
        } else {
            std::cout << "Formato de hora no válido. Use el formato HH:MM (por ejemplo, 13:30)." << std::endl;
            // Limpiar el búfer del cin en caso de entrada adicional
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return horario;
}

void limpiarBufferEntrada() {
    // Limpia el búfer de entrada hasta encontrar un salto de línea
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Función para verificar si un doctor tiene citas asignadas
bool doctorTieneCitasAsignadas(const std::vector<evento>& agenda, const std::string& nombreDoctor, const std::vector<std::vector<std::string>>& consultoriosDoctores) {
    for (const auto& evento : agenda) {
        int consultorioEvento = evento.consultorio;
        std::string nombreDoctorEvento;

        if (consultorioEvento >= 1 && consultorioEvento <= consultoriosDoctores.size()) {
            nombreDoctorEvento = consultoriosDoctores[consultorioEvento - 1][0];
        } else {
            nombreDoctorEvento = "No asignado";
        }

        if (nombreDoctorEvento == nombreDoctor) {
            return true; // El doctor tiene al menos una cita asignada
        }
    }
    return false; // El doctor no tiene citas asignadas
}

// Función para eliminar un doctor
void eliminarDoctor(std::vector<std::vector<std::string>>& consultoriosDoctores, std::vector<evento>& agenda) {
    if (!consultoriosDoctores.empty()) {
        std::cout << "Doctores registrados:" << std::endl;
        for (int i = 0; i < consultoriosDoctores.size(); i++) {
            std::cout << i + 1 << ". " << consultoriosDoctores[i][0] << std::endl;
        }

        std::cout << "Ingrese el número del doctor que desea eliminar: ";
        int numDoctor = obtenerEnteroValido();

        if (numDoctor >= 1 && numDoctor <= consultoriosDoctores.size()) {
            std::string nombreDoctor = consultoriosDoctores[numDoctor - 1][0];

            // Verifica si el doctor tiene citas asignadas antes de eliminarlo
            if (!doctorTieneCitasAsignadas(agenda, nombreDoctor, consultoriosDoctores)) {
                // Elimina al doctor solo si no tiene citas asignadas
                consultoriosDoctores.erase(consultoriosDoctores.begin() + numDoctor - 1);
                std::cout << "Doctor \"" << nombreDoctor << "\" eliminado con éxito." << std::endl;
            } else {
                std::cout << "No se puede eliminar al doctor porque tiene citas asignadas." << std::endl;
            }
        } else {
            std::cout << "Número de doctor no válido." << std::endl;
        }
    } else {
        std::cout << "No hay doctores para eliminar." << std::endl;
    }
}


void gestionarDoctores(std::vector<std::vector<std::string>>& consultoriosDoctores, std::vector<evento>& agenda) {
    std::string nuevoDoctor;
    std::string diasTrabajo;
    HorarioTrabajo horario;  // Mueve la declaración aquí para que sea accesible en todos los casos
    while (true) {
        std::cout << "MENÚ DE GESTIÓN DE DOCTORES" << std::endl;
        std::cout << "1. Agregar Doctor" << std::endl;
        std::cout << "2. Editar Doctor" << std::endl;
        std::cout << "3. Asignar Doctor a Consultorio" << std::endl;
        std::cout << "4. Eliminar Doctor" << std::endl;
        std::cout << "5. Mostrar horario de los Doctores" << std::endl;
        std::cout << "0. Volver al menú principal" << std::endl;
        std::cout << "Seleccione una opción: ";

        int opc = obtenerEnteroValido();

        switch (opc) {
            case 1: // Agregar Doctor
                std::cout << "Ingrese el nombre del nuevo doctor: ";
                std::getline(std::cin, nuevoDoctor);
                
                while (nuevoDoctor.find_first_not_of(' ') == std::string::npos) {
                    std::cout << "Debe ingresar un nombre completo. Vuelva a ingresar el nombre: ";
                    std::getline(std::cin, nuevoDoctor);
                }
            
                diasTrabajo = obtenerDiasTrabajo();
            
                while (!validarDiasTrabajo(diasTrabajo)) {
                    std::cout << "Debe seleccionar al menos dos días de trabajo. Vuelva a ingresar los días." << std::endl;
                    diasTrabajo = obtenerDiasTrabajo();
                }
            
                horario = obtenerHorarioTrabajo();  // Asigna los valores a la variable existente
            
                consultoriosDoctores.push_back({ nuevoDoctor, "", diasTrabajo, std::to_string(horario.horaEntrada), std::to_string(horario.minutoEntrada), std::to_string(horario.horaSalida), std::to_string(horario.minutoSalida) });
                std::cout << "Doctor agregado con éxito." << std::endl;
                break;
                
            case 2: // Editar Doctor
            {
                if (!consultoriosDoctores.empty()) {
                    std::cout << "Doctores registrados:" << std::endl;
                    for (int i = 0; i < consultoriosDoctores.size(); i++) {
                        std::cout << i + 1 << ". " << consultoriosDoctores[i][0] << std::endl;
                    }
            
                    std::cout << "Ingrese el número del doctor que desea editar: ";
                    int numDoctor = obtenerEnteroValido();
            
                    // Verifica si numDoctor es un índice válido
                    if (numDoctor >= 1 && numDoctor <= consultoriosDoctores.size()) {
            
                        std::cout << "Ingrese el nuevo nombre del doctor: ";
                        std::getline(std::cin, consultoriosDoctores[numDoctor - 1][0]);
            
                        while (consultoriosDoctores[numDoctor - 1][0].find_first_not_of(' ') == std::string::npos) {
                            std::cout << "Debe ingresar un nombre completo. Vuelva a ingresar el nombre: ";
                            std::getline(std::cin, consultoriosDoctores[numDoctor - 1][0]);
                        }
                        bool diasDeLaSemana = false;
                        char editarDias;
                        do {
                            std::cout << "¿Desea editar los días de trabajo? (s/n): ";
                            std::cin >> editarDias;
                            if (std::cin.fail() || (std::cin.peek() != '\n') || (editarDias != 's' && editarDias != 'S' && editarDias != 'n' && editarDias != 'N')) {
                                std::cout << "Por favor, ingrese 's' o 'n'." << std::endl;
                                std::cin.clear();  // Limpia el indicador de error
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Descarta la entrada incorrecta
                            } else if (std::cin.peek() != '\n') {
                                // Limpiar el búfer del cin en caso de entrada adicional
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            } else {
                                diasDeLaSemana = true;
                            }
                        } while (!diasDeLaSemana);
            
                        if (editarDias == 's' || editarDias == 'S') {
                            diasTrabajo = obtenerDiasTrabajo();
            
                            while (!validarDiasTrabajo(diasTrabajo)) {
                                std::cout << "Debe seleccionar al menos dos días de trabajo. Vuelva a ingresar los días." << std::endl;
                                diasTrabajo = obtenerDiasTrabajo();
                            }
            
                            consultoriosDoctores[numDoctor - 1][2] = diasTrabajo;
                        }
            
                        char editarHorario;
                        bool entradaHorarioValida = false;
                        do {
                            std::cout << "¿Desea editar el horario de trabajo? (s/n): ";
                            std::cin >> editarHorario;
                            if (std::cin.fail() || (std::cin.peek() != '\n') || (editarHorario != 's' && editarHorario != 'S' && editarHorario != 'n' && editarHorario != 'N')) {
                                std::cout << "Por favor, ingrese 's' o 'n'." << std::endl;
                                std::cin.clear();  // Limpia el indicador de error
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Descarta la entrada incorrecta
                            } else if (std::cin.peek() != '\n') {
                                // Limpiar el búfer del cin en caso de entrada adicional
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            } else {
                                entradaHorarioValida = true;
                            }
                        } while (!entradaHorarioValida);
                        if (editarHorario == 's' || editarHorario == 'S') {
                            horario = obtenerHorarioTrabajo();
                        
                            consultoriosDoctores[numDoctor - 1][3] = std::to_string(horario.horaEntrada);
                            consultoriosDoctores[numDoctor - 1][4] = std::to_string(horario.minutoEntrada);
                            consultoriosDoctores[numDoctor - 1][5] = std::to_string(horario.horaSalida);
                            consultoriosDoctores[numDoctor - 1][6] = std::to_string(horario.minutoSalida);
                        }
            
                        std::cout << "Doctor editado con éxito." << std::endl;
                    } else {
                        std::cout << "Número de doctor no válido." << std::endl;
                    }
                } else {
                    std::cout << "No hay doctores para editar." << std::endl;
                }
            
                break;
            }

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
                eliminarDoctor(consultoriosDoctores, agenda);
                
                break;
            case 5: // Mostrar Horarios de Doctores
                if (!consultoriosDoctores.empty()) {
                    std::cout << "Horarios de los Doctores:" << std::endl;
                    for (int i = 0; i < consultoriosDoctores.size(); i++) {
                        std::cout << i + 1 << ". " << "Doctor: " << consultoriosDoctores[i][0] << std::endl;
                        std::cout << "   Días de trabajo: " << consultoriosDoctores[i][2] << std::endl;
                        std::cout << "   Horario: " << consultoriosDoctores[i][3] << ":" << consultoriosDoctores[i][4] << " - "
                                  << consultoriosDoctores[i][5] << ":" << consultoriosDoctores[i][6] << std::endl;
                      if (!consultoriosDoctores[i][1].empty()) {
                            std::cout << "   Consultorio asignado: " << consultoriosDoctores[i][1] << std::endl;
                        } else {
                            std::cout << "   Consultorio asignado: No asignado" << std::endl;
                        }
                    }
                } else {
                    std::cout << "No hay doctores registrados." << std::endl;
                }
                break;
            case 0: // Volver al menú principal
                return;

            default:
                std::cout << "Opción no válida. Por favor, seleccione un número válido" << std::endl;
        }
    }
}

void obtenerFechaValida(int& dia, int& mes, int& año) {
    dia = 0;
    mes = 0;
    año = 0;

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
                // Verificar si la fecha es posterior a la fecha actual
                if ((año < añoActual) || (año == añoActual && mes < mesActual) ||
                    (año == añoActual && mes == mesActual && dia < diaActual)) {
                    std::cout << "La fecha no puede ser anterior a la fecha actual. Ingrese otra fecha." << std::endl;
                } else {
                    break;
                }
            }
        } else {
            // Verificar si la fecha es posterior a la fecha actual
            if ((año < añoActual) || (año == añoActual && mes < mesActual) ||
                (año == añoActual && mes == mesActual && dia < diaActual)) {
                std::cout << "La fecha no puede ser anterior a la fecha actual. Ingrese otra fecha." << std::endl;
            } else {
                break;
            }
        }
    }
}

void obtenerHoraValida(int& hora, int& minuto) {
    hora = 0;
    minuto = 0;
    while (true) {
        std::string horaStr;
        std::cout << "Ingrese la hora del evento (HH:MM): ";
        std::cin >> horaStr;

        if (horaStr.size() == 5 && horaStr[2] == ':' && std::isdigit(horaStr[0]) && std::isdigit(horaStr[1]) && std::isdigit(horaStr[3]) && std::isdigit(horaStr[4])) {
            hora = std::stoi(horaStr.substr(0, 2));
            minuto = std::stoi(horaStr.substr(3, 2));
            if (hora >= 0 && hora < 24 && minuto >= 0 && minuto < 60) {
                // Verificar duración mínima de 30 minutos
                int duracionTotalMinutos = hora * 60 + minuto;
                if (duracionTotalMinutos + 30 <= 24 * 60) {
                    break;
                } else {
                    std::cout << "La duración del evento debe ser de al menos 30 minutos. Ingrese una hora válida." << std::endl;
                }
            }
        }
        std::cout << "Formato de hora no válido. Use el formato HH:MM (por ejemplo, 13:30)." << std::endl;
    }
}

void obtenerHoraValidaFinal(int& hora, int& minuto, int horaInicio, int minutoInicio) {
    hora = 0;
    minuto = 0;
    while (true) {
        std::string horaStr;
        std::cout << "Ingrese la hora en que finaliza la cita (HH:MM): ";
        std::cin >> horaStr;

        if (horaStr.size() == 5 && horaStr[2] == ':' && std::isdigit(horaStr[0]) && std::isdigit(horaStr[1]) && std::isdigit(horaStr[3]) && std::isdigit(horaStr[4])) {
            hora = std::stoi(horaStr.substr(0, 2));
            minuto = std::stoi(horaStr.substr(3, 2));
            if (hora >= 0 && hora < 24 && minuto >= 0 && minuto < 60) {
                // Verificar duración mínima de 30 minutos
                int duracionTotalMinutos = (hora - horaInicio) * 60 + (minuto - minutoInicio);
                if (duracionTotalMinutos >= 30) {
                    break;
                } else {
                    std::cout << "La duración del evento debe ser de al menos 30 minutos. Ingrese una hora válida." << std::endl;
                }
            }
        }
        std::cout << "Formato de hora no válido. Use el formato HH:MM (por ejemplo, 13:30)." << std::endl;
    }
}


std::string obtenerNombreDia(int dia, int mes, int anio) {
    struct tm fecha = {0};
    fecha.tm_year = anio - 1900;
    fecha.tm_mon = mes - 1;
    fecha.tm_mday = dia;

    const char* nombresDias[] = { "Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado" };

    std::mktime(&fecha);

    return nombresDias[fecha.tm_wday];
}

bool eventoInterfiere(const evento& nuevaCita, const std::vector<evento>& agenda, const std::vector<std::vector<std::string>>& consultoriosDoctores) {
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

    // Verificar si el doctor trabaja en el día de la nueva cita
    const std::vector<std::string>& doctorInfo = consultoriosDoctores[nuevaCita.consultorio - 1];
    if (doctorInfo[2].find(obtenerNombreDia(nuevaCita.dia, nuevaCita.mes, nuevaCita.año)) == std::string::npos) {
        return true; // El doctor no trabaja en este día
    }

    // Verificar si la nueva cita está dentro del horario de trabajo del doctor
    int horaInicioDoctor = std::stoi(doctorInfo[3]);
    int minutoInicioDoctor = std::stoi(doctorInfo[4]);
    int horaFinDoctor = std::stoi(doctorInfo[5]);
    int minutoFinDoctor = std::stoi(doctorInfo[6]);

    if ((nuevaCita.hora < horaInicioDoctor) ||
        (nuevaCita.hora == horaInicioDoctor && nuevaCita.minuto < minutoInicioDoctor) ||
        (nuevaCita.horaFin > horaFinDoctor) ||
        (nuevaCita.horaFin == horaFinDoctor && nuevaCita.minutoFin > minutoFinDoctor)) {
        return true; // La nueva cita está fuera del horario de trabajo del doctor
    }

    return false; // No hay interferencia
}



void agregarEvento(std::vector<evento>& agenda, const std::vector<std::vector<std::string>>& consultoriosDoctores) {
    bool doctorAsignado = false;

    // Verificar si hay al menos un doctor con consultorio asignado
    for (const auto& doctor : consultoriosDoctores) {
        if (!doctor[1].empty()) {
            doctorAsignado = true;
            break;
        }
    }

    if (!doctorAsignado) {
        std::cout << "No se pueden agregar eventos hasta que haya al menos un doctor asignado a un consultorio." << std::endl;
        return;
    }

    evento nuevoEvento;

    std::cout << "Ingrese el nombre del paciente: ";
    std::getline(std::cin, nuevoEvento.nombres);
    
    while (nuevoEvento.nombres.find_first_not_of(' ') == std::string::npos) {
        std::cout << "Debe ingresar un nombre completo. Vuelva a ingresar el nombre: ";
        std::getline(std::cin, nuevoEvento.nombres);
    }   

    std::cout << "Doctores disponibles para asignar cita:" << std::endl;
    for (size_t i = 0; i < consultoriosDoctores.size(); ++i) {
        // Solo mostrar doctores con consultorio asignado
        if (!consultoriosDoctores[i][1].empty()) {
            std::cout << i + 1 << ". " << consultoriosDoctores[i][0] << " - Consultorio: " << consultoriosDoctores[i][1] << std::endl;
        }
    }

    int numDoctor;  // Mover la declaración aquí
    std::cout << "Seleccione el número del Doctor al que desea asignar al paciente: ";
    numDoctor = obtenerEnteroValido();  // Asignar el valor aquí

    if (numDoctor >= 1 && numDoctor <= consultoriosDoctores.size() && !consultoriosDoctores[numDoctor - 1][1].empty()) {
        // Asignar el consultorio al evento
        nuevoEvento.consultorio = numDoctor;
    } else {
        std::cout << "Número de doctor no válido o el doctor no tiene consultorio asignado." << std::endl;
        return;
    }

    obtenerFechaValida(nuevoEvento.dia, nuevoEvento.mes, nuevoEvento.año);
    obtenerHoraValida(nuevoEvento.hora, nuevoEvento.minuto);
    obtenerHoraValidaFinal(nuevoEvento.horaFin, nuevoEvento.minutoFin, nuevoEvento.hora, nuevoEvento.minuto);

    while (eventoInterfiere(nuevoEvento, agenda, consultoriosDoctores)) {
        std::cout << "La cita coincide con otra en el mismo consultorio o el Doctor no trabaja." << std::endl;
        std::cout << "Horarios de los Doctores:" << std::endl;
        for (int i = 0; i < consultoriosDoctores.size(); i++) {
            std::cout << i + 1 << ". " << "Doctor: " << consultoriosDoctores[i][0] << std::endl;
            std::cout << "   Días de trabajo: " << consultoriosDoctores[i][2] << std::endl;
            std::cout << "   Horario: " << consultoriosDoctores[i][3] << ":" << consultoriosDoctores[i][4] << " - "
                      << consultoriosDoctores[i][5] << ":" << consultoriosDoctores[i][6] << std::endl;
            std::cout << "   Consultorio asignado: " << consultoriosDoctores[i][1] << std::endl;
        }
        std::cout << "¿Desea cambiar la fecha, el Doctor o cancelar la operación?" << std::endl;
        std::cout << "1. Cambiar la fecha y hora" << std::endl;
        std::cout << "2. Cambiar el consultorio" << std::endl;
        std::cout << "3. Cancelar" << std::endl;
        std::cout << "Seleccione una opción: ";
        
        int cambio = obtenerEnteroValido();

        switch (cambio) {
            case 1: // Cambiar la fecha
                obtenerFechaValida(nuevoEvento.dia, nuevoEvento.mes, nuevoEvento.año);
                obtenerHoraValida(nuevoEvento.hora, nuevoEvento.minuto);
                obtenerHoraValidaFinal(nuevoEvento.horaFin, nuevoEvento.minutoFin, nuevoEvento.hora, nuevoEvento.minuto);
                break;
            case 2: // Cambiar el consultorio
                std::cout << "Doctores disponibles para asignar cita:" << std::endl;
                for (size_t i = 0; i < consultoriosDoctores.size(); ++i) {
                    // Solo mostrar doctores con consultorio asignado
                    if (!consultoriosDoctores[i][1].empty()) {
                        std::cout << i + 1 << ". " << consultoriosDoctores[i][0] << " - Consultorio: " << consultoriosDoctores[i][1] << std::endl;
                    }
                }
            
                std::cout << "Seleccione el número del Doctor al que desea asignar al paciente: ";
                numDoctor = obtenerEnteroValido();
            
                if (numDoctor >= 1 && numDoctor <= consultoriosDoctores.size() && !consultoriosDoctores[numDoctor - 1][1].empty()) {
                    // Asignar el consultorio al evento
                    nuevoEvento.consultorio = numDoctor;
                } else {
                    std::cout << "Número de doctor no válido o el doctor no tiene consultorio asignado." << std::endl;
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

        std::getline(std::cin, citaAEditar.nombres);

        while (citaAEditar.nombres.find_first_not_of(' ') == std::string::npos) {
            std::cout << "Debe ingresar un nombre completo: ";
            std::getline(std::cin, citaAEditar.nombres);
        }

        std::cout << "Doctores disponibles para asignar cita:" << std::endl;
        for (size_t i = 0; i < consultoriosDoctores.size(); ++i) {
            // Solo mostrar doctores con consultorio asignado
            if (!consultoriosDoctores[i][1].empty()) {
                std::cout << i + 1 << ". " << consultoriosDoctores[i][0] << " - Consultorio: " << consultoriosDoctores[i][1] << std::endl;
            }
        }

        int numConsultorio;
        std::cout << "Seleccione el número del Doctor al que desea asignar al paciente: ";
        std::cin >> numConsultorio;

        if (numConsultorio >= 1 && numConsultorio <= consultoriosDoctores.size() && !consultoriosDoctores[numConsultorio - 1][1].empty()) {
            citaAEditar.consultorio = numConsultorio;
        } else {
            std::cout << "Número de doctor no válido o el doctor no tiene consultorio asignado." << std::endl;
            return;
        }

        obtenerFechaValida(citaAEditar.dia, citaAEditar.mes, citaAEditar.año);
        obtenerHoraValida(citaAEditar.hora, citaAEditar.minuto);
        obtenerHoraValidaFinal(citaAEditar.horaFin, citaAEditar.minutoFin, citaAEditar.hora, citaAEditar.minuto);

        // Lógica para obtener y validar la nueva fecha y hora de la cita

        while (eventoInterfiere(citaAEditar, agenda, consultoriosDoctores)) {
            std::cout << "La cita coincide con otra en el mismo consultorio o el Doctor no trabaja." << std::endl;
            std::cout << "Horarios de los Doctores:" << std::endl;
            for (int i = 0; i < consultoriosDoctores.size(); i++) {
                std::cout << i + 1 << ". " << "Doctor: " << consultoriosDoctores[i][0] << std::endl;
                std::cout << "   Días de trabajo: " << consultoriosDoctores[i][2] << std::endl;
                std::cout << "   Horario: " << consultoriosDoctores[i][3] << ":" << consultoriosDoctores[i][4] << " - "
                          << consultoriosDoctores[i][5] << ":" << consultoriosDoctores[i][6] << std::endl;
                std::cout << "   Consultorio asignado: " << consultoriosDoctores[i][1] << std::endl;
            }
            std::cout << "¿Desea cambiar la fecha, el Doctor o cancelar la operación?" << std::endl;
            std::cout << "1. Cambiar la fecha y hora" << std::endl;
            std::cout << "2. Cambiar el consultorio" << std::endl;
            std::cout << "3. Cancelar" << std::endl;
            std::cout << "Seleccione una opción: ";

            int cambio;
            std::cin >> cambio;

            switch (cambio) {
                case 1: // Cambiar la fecha
                    obtenerFechaValida(citaAEditar.dia, citaAEditar.mes, citaAEditar.año);
                    obtenerHoraValida(citaAEditar.hora, citaAEditar.minuto);
                    obtenerHoraValidaFinal(citaAEditar.horaFin, citaAEditar.minutoFin, citaAEditar.hora, citaAEditar.minuto);
                    break;
                case 2: // Cambiar el consultorio
                    std::cout << "Doctores disponibles para asignar cita:" << std::endl;
                    for (size_t i = 0; i < consultoriosDoctores.size(); ++i) {
                        // Solo mostrar doctores con consultorio asignado
                        if (!consultoriosDoctores[i][1].empty()) {
                            std::cout << i + 1 << ". " << consultoriosDoctores[i][0] << " - Consultorio: " << consultoriosDoctores[i][1] << std::endl;
                        }
                    }
                    std::cout << "Seleccione el número del Doctor al que desea asignar al paciente: ";
                    std::cin >> numConsultorio;
                    if (numConsultorio >= 1 && numConsultorio <= consultoriosDoctores.size() && !consultoriosDoctores[numConsultorio - 1][1].empty()) {
                        citaAEditar.consultorio = numConsultorio;
                    } else {
                        std::cout << "Número de doctor no válido o el doctor no tiene consultorio asignado." << std::endl;
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
    leerDoctoresDeArchivo(consultoriosDoctores, "doctores.txt");
    leerEventosDeArchivo(agenda, consultoriosDoctores, "eventos.txt");
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
                gestionarDoctores(consultoriosDoctores, agenda);
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
            
                        std::cout << "Cita " << i + 1 << " Nombre del Paciente: " << agenda[i].nombres << " Doctor: " << agenda[i].nombreDoctor
                                  << " - Consultorio: " << consultoriosDoctores[i][1] << " Fecha: " << agenda[i].dia << "/" << agenda[i].mes << "/" << agenda[i].año
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
                escribirDoctoresEnArchivo(consultoriosDoctores, "doctores.txt");
                escribirEventosEnArchivo(agenda, consultoriosDoctores, "eventos.txt");
                std::cout << "Saliendo del programa" << std::endl;
                return 0;
            default:
                std::cout << "Opción no válida. Por favor, seleccione un número válido" << std::endl;
                    
        }//fin del switch case
            
    }
    
    return 0;
}