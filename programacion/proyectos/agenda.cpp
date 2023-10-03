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
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Carácter no válido. Ingrese un número." << std::endl;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer de entrada
    return numero;
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

int main() {
    std::vector<evento> agenda; // Declaración del vector llamado agenda para guardar los eventos

    while (true) {
        std::cout << "MENU DE OPCIONES" << std::endl;
        std::cout << "1. Agregar un evento" << std::endl;
        std::cout << "2. Mostrar todos los eventos" << std::endl;
        std::cout << "3. Mostrar tiempo para el evento" << std::endl;
        std::cout << "4. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";

        int opc = obtenerEnteroValido();

        evento evento; // Declaración de una variable evento para guardar temporalmente los datos de un evento

        switch (opc) {
            case 1: // Agregar eventos
                std::cout << "Ingrese el nombre del evento: ";
                std::getline(std::cin, evento.nombres);

                while (true) {
                    std::cout << "Ingrese la fecha del evento (días/meses/años): ";
                    char separador; // Variable para almacenar el carácter separador ("/")
                    if (!(std::cin >> evento.dia >> separador >> evento.mes >> separador >> evento.año) || separador != '/') {// Esta linea es para que el usuario ingrese bien la fecha por ejemplo 12/12/2023 si ingresa otra fecha lo regresa a ingresar otra vez
                        std::cout << "Formato de fecha no válido. Use el formato días/meses/años (por ejemplo, 12/9/23)." << std::endl;
                        std::cin.clear();//limpia para volver ingresar la fecha 
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// Llama a la libreria limits para eliminar cualquier entrada incorrecta
                        continue; // Volver a solicitar la fecha
                    }

                    if (esFechaValida(evento.dia, evento.mes, evento.año)) {// Llama a la funcion para que el uisuario no ingrese una fecha incorrecta 
                        break; // La fecha es válida, salimos del bucle
                    } else {
                        std::cout << "Fecha no válida. Ingrese otra fecha." << std::endl;
                    }
                }

                while (true) {
                    std::cout << "Ingrese la hora del evento (0-23): ";
                    evento.hora = obtenerEnteroValido();// llama a la funcion obtenerEnteroValido para que no ingrese una letra 
                    std::cout << "Ingrese los minutos del evento (0-59): ";
                    evento.minuto = obtenerEnteroValido();

                    if (esHoraValida(evento.hora, evento.minuto)) {//llama a la funcion para que el usuario no ingrese una fecah incorrecta 
                        break; // La hora es válida, salimos del bucle
                    } else {
                        std::cout << "Hora no válida. Ingrese otra hora." << std::endl;
                    }
                }

                agenda.push_back(evento); // Lo agrega al vector
                break;
            case 2: // Mostrar eventos
                if (!agenda.empty()) { // Verificar si hay eventos en la agenda
                    std::cout << "Lista de Eventos:" << std::endl;
                    for (int i = 0; i < agenda.size(); i++) { // agenda.size muestra el tamaño del vector 
                        std::cout << "Evento " << i + 1 << ": " << agenda[i].nombres << " Fecha: " << agenda[i].dia << "/" << agenda[i].mes << "/" << agenda[i].año//muestra todos los datos ingresador del evento
                                  << " Hora: " << agenda[i].hora << ":" << agenda[i].minuto << std::endl;
                    }
                } else {
                    std::cout << "No hay eventos para mostrar" << std::endl;
                }
                break;
            case 3: // Calcular tiempo para el evento
                if (!agenda.empty()) { // Verificar si hay eventos en la agenda
                    std::cout << "Ingrese el número de evento: ";
                    int numEvento = obtenerEnteroValido(); // Variable que se utilizará para leer el número del evento que el usuario quiere consultar y llama a la funcion para que no ingrese una tecla incorrecta 

                    if (numEvento >= 1 && numEvento <= agenda.size()) { // Verificar si el número del evento es válido y si el tamaño de la agenda es válido
                        time_t ahora = time(0); // Obtiene la hora actual del sistema y la guarda en la variable ahora
                        tm eventoTime = {}; // Se declara una estructura que sirve para representar la fecha y la hora del evento
                        eventoTime.tm_year = agenda[numEvento - 1].año - 1900; // Se le resta al 1900 al año por la estructura "tm" si ingresa 2023 se le resta 1900 y queda 123 y así lo lee
                        eventoTime.tm_mon = agenda[numEvento - 1].mes - 1;
                        eventoTime.tm_mday = agenda[numEvento - 1].dia;
                        eventoTime.tm_hour = agenda[numEvento - 1].hora;
                        eventoTime.tm_min = agenda[numEvento - 1].minuto;
                        eventoTime.tm_sec = 0; // Segundos en cero

                        time_t eventoTiempo = mktime(&eventoTime); // La estructura eventoTime se convierte en un valor de tiempo (time_t) que representa la fecha y hora del evento seleccionado
                        double segundosRestantes = difftime(eventoTiempo, ahora); // Esto calcula la diferencia de segundos entre el tiempo del evento "eventoTiempo" y el tiempo actual "ahora" que dice cuántos segundos faltan para que ocurra el evento con el difftime

                        if (segundosRestantes < 0) { // Verifica si los segundos son menores a cero
                            std::cout << "El evento \"" << agenda[numEvento - 1].nombres << "\" ya ha pasado" << std::endl; // Si los segundos están por debajo de 0, muestra este mensaje
                        } else {
                            //variables con los segundos de un minuto, hora,dias,meses,años
                            const int segundosEnMinuto = 60;
                            const int segundosEnHora = 3600;
                            const int segundosEnDia = 86400;
                            const int segundosEnMes = 2592000; // Asumiendo un mes promedio de 30.44 días
                            const int segundosEnAño = 31536000; // Asumiendo un año promedio de 365.25 días

                            int añosRestantes = static_cast<int>(segundosRestantes / segundosEnAño); //la operacion aqui declaramos un entero añosRestantes que es igual a segundosRestantes que esta variable esta en double y que almacena la fecha ingresada en segundos 
                            segundosRestantes -= añosRestantes * segundosEnAño;                      //se divide en segundos en años que lo declaramos luego años restantes es igual menos segundos restantes multiplicado por segundos en años y lo mismo en las demas lineas

                            int mesesRestantes = static_cast<int>(segundosRestantes / segundosEnMes);
                            segundosRestantes -= mesesRestantes * segundosEnMes;

                            int diasRestantes = static_cast<int>(segundosRestantes / segundosEnDia);
                            segundosRestantes -= diasRestantes * segundosEnDia;

                            int horasRestantes = static_cast<int>(segundosRestantes / segundosEnHora);
                            segundosRestantes -= horasRestantes * segundosEnHora;

                            int minutosRestantes = static_cast<int>(segundosRestantes / segundosEnMinuto);// esta solamente convierte segundos en minutos 

                            std::cout << "Tiempo restante para el evento \"" << agenda[numEvento - 1].nombres << "\":" << std::endl;
                            if (añosRestantes > 0) { //agara la variable ya convertidas en años y la muestra junto con las demas lineas de este if 
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
                    } else { // Si selecciona un evento que no es válido, muestra este mensaje
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