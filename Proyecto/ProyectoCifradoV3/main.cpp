#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include "ListaUsuarios.h"
#include "ListaVehiculos.h"
#include "ListaDoble.h"
#include "GestorFechas.h"
#include "GestorArchivos.h"
#include "CifradoPlaca.h"
#include "Validador.h"

using namespace std;

// ============================================================
//  MENU USUARIOS
// ============================================================
void menuUsuarios(ListaUsuarios& lu, ListaDoble& lr, ListaVehiculos& lv) {
    int op;
    string ced;
    do {
        system("cls");

        cout << "\n========== GESTION DE USUARIOS ==========\n";
        cout << "1. Registrar Usuario\n";
        cout << "2. Listar Usuarios\n";
        cout << "3. Modificar Usuario\n";
        cout << "4. Eliminar Usuario\n";
        cout << "5. Busqueda binaria por cedula\n";
        cout << "6. Volver al Menu Principal\n";

        op = Validador::leerOpcionPorClic(2, 7);

        if (op == 1) {
            // Cedula
            do {
                cout << "  Cedula Ecuatoriana (10 digitos): ";
                cin >> ced;
                cin.ignore(10000, '\n');
                if (!Validador::validarCedula(ced))
                    cout << "  [!] Cedula invalida (algoritmo Modulo 10 fallido).\n";
            } while (!Validador::validarCedula(ced));

            if (lu.buscar(ced)) {
                cout << "  [!] Ya existe un usuario con esa cedula.\n";
                continue;
            }

            // Nombre y Apellido: usa leerTextoValido que hace trim y valida
            string nom = Validador::leerTextoValido("  Nombre: ");
            string ape = Validador::leerTextoValido("  Apellido: ");

            lu.crear(new Usuario(Validador::aMayusculas(nom),
                                 Validador::aMayusculas(ape), ced));
            cout << "  [OK] Usuario registrado exitosamente.\n";
            GestorArchivos::guardarTodo(lu, lv, lr);

        } else if (op == 2) {
            lu.reportar();

        } else if (op == 3) {
            cout << "  Cedula del usuario a modificar: ";
            cin >> ced;
            cin.ignore(10000, '\n');
            if (!lu.buscar(ced)) {
                cout << "  [!] Usuario no encontrado.\n";
                continue;
            }
            string nom = Validador::leerTextoValido("  Nuevo Nombre: ");
            string ape = Validador::leerTextoValido("  Nuevo Apellido: ");

            lu.actualizar(ced, Validador::aMayusculas(nom),
                               Validador::aMayusculas(ape));
            cout << "  [OK] Usuario modificado con exito.\n";
            GestorArchivos::guardarTodo(lu, lv, lr);

        } else if (op == 4) {
            cout << "  Cedula del usuario a eliminar: ";
            cin >> ced;
            cin.ignore(10000, '\n');
            lr.eliminarCascadaUsuario(ced);
            if (lu.eliminar(ced)) {
                cout << "  [OK] Usuario y sus turnos eliminados del sistema.\n";
                GestorArchivos::guardarTodo(lu, lv, lr);
            } else
                cout << "  [!] Usuario no encontrado.\n";
        } else if (op == 5){
            system("cls");
            cout << "\n========== BÚSQUEDA BINARIA DE USUARIO ==========\n";
            
            // 1. Solicitar y validar la cédula que se va a buscar
            do {
                cout << "  Ingrese la Cedula a buscar (10 digitos): ";
                cin >> ced;
                cin.ignore(10000, '\n');
                if (!Validador::validarCedula(ced))
                    cout << "  [!] Cedula invalida. Intente de nuevo.\n";
            } while (!Validador::validarCedula(ced));

            cout << "\n  [SISTEMA] Ordenando memoria dinamicamente y aplicando algoritmo binario...\n";
            
            // 2. Llamar a tu nueva función extrema de punteros puros
            Usuario* u = lu.busquedaBinariaPorCedula(ced);

            // 3. Mostrar los resultados en pantalla
            if (!u) {
                cout << "  [!] No se encontro ningun usuario registrado con la cedula: " << ced << "\n";
            } else {
                cout << "\n  ========================================\n";
                cout << "  [USUARIO ENCONTRADO CON EXITO!]\n";
                cout << "  Cedula:    " << u->getCedula() << "\n";
                cout << "  Nombre:    " << u->getNombre() << "\n";
                cout << "  Apellido:  " << u->getApellido() << "\n";
                //cout << "  Correo:    " << u->getCorreo() << "\n";
                cout << "  ========================================\n";
            }
        }

        if (op != 6) {
            cout << "\n";
            system("pause"); 
        }
    } while (op != 6);
}

// ============================================================
//  MENU VEHICULOS
// ============================================================
void menuVehiculos(ListaVehiculos& lv, ListaDoble& lr, ListaUsuarios& lu) {
    int op;
    string placa, nuevaPlaca;
    do {
        system("cls");
        cout << "\n========== GESTION DE VEHICULOS ==========\n";
        cout << "1. Registrar Vehiculo\n";
        cout << "2. Listar Vehiculos\n";
        cout << "3. Modificar Placa\n";
        cout << "4. Eliminar Vehiculo\n";
        cout << "5. Busqueda Binaria por placa\n";
        cout << "6. Volver al Menu Principal\n";

        op = Validador::leerOpcionPorClic(2, 7);

        if (op == 1) {
            do {
                cout << "  Placa (Ej: ABC-1234): ";
                cin >> placa;
                cin.ignore(10000, '\n');
                if (!Validador::validarPlaca(placa))
                    cout << "  [!] Formato invalido o provincia no reconocida.\n";
            } while (!Validador::validarPlaca(placa));

            string placaEst = Validador::aMayusculas(placa);
            if (lv.buscar(placaEst)) {
                cout << "  [!] Ese vehiculo ya esta registrado.\n";
                continue;
            }
            lv.crear(new Vehiculo(placaEst));
            cout << "  [OK] Vehiculo registrado: " << placaEst << "\n";
            GestorArchivos::guardarTodo(lu, lv, lr);

        } else if (op == 2) {
            lv.reportar();

        } else if (op == 3) {
            cout << "  Placa actual: ";
            cin >> placa;
            cin.ignore(10000, '\n');
            string placaEst = Validador::aMayusculas(placa);
            if (!lv.buscar(placaEst)) {
                cout << "  [!] Vehiculo no encontrado.\n";
                continue;
            }
            do {
                cout << "  Nueva Placa: ";
                cin >> nuevaPlaca;
                cin.ignore(10000, '\n');
                if (!Validador::validarPlaca(nuevaPlaca))
                    cout << "  [!] Formato o provincia invalida.\n";
            } while (!Validador::validarPlaca(nuevaPlaca));

            string nuevaEst = Validador::aMayusculas(nuevaPlaca);
            if (lv.buscar(nuevaEst)) {
                cout << "  [!] Esa placa ya esta en uso.\n";
                continue;
            }
            lv.actualizar(placaEst, nuevaEst);
            cout << "  [OK] Placa actualizada a: " << nuevaEst << "\n";
            GestorArchivos::guardarTodo(lu, lv, lr);

        } else if (op == 4) {
            cout << "  Placa a eliminar: ";
            cin >> placa;
            cin.ignore(10000, '\n');
            string placaEst = Validador::aMayusculas(placa);
            lr.eliminarCascadaVehiculo(placaEst);
            if (lv.eliminar(placaEst)) {
                cout << "  [OK] Vehiculo y su turno activo eliminados.\n";
                GestorArchivos::guardarTodo(lu, lv, lr);
            } else
                cout << "  [!] Vehiculo no encontrado.\n";
        } else if (op == 5){
            system("cls");
            cout << "\n========== BuSQUEDA BINARIA DE VEHICULO ==========\n";
            
            do {
                cout << "  Ingrese Placa a buscar (Ej: ABC-1234): ";
                cin >> placa;
                cin.ignore(10000, '\n');
                if (!Validador::validarPlaca(placa))
                    cout << "  [!] Formato invalido.\n";
            } while (!Validador::validarPlaca(placa));

            // CORRECCIÓN CRÍTICA: Convertimos estrictamente a mayúsculas
            // para que coincida con la tabla ASCII de nuestra búsqueda binaria.
            string placaEst = Validador::aMayusculas(placa);

            cout << "\n  [SISTEMA] Ordenando memoria dinamicamente...\n";

            Vehiculo* v = lv.busquedaBinariaPorPlaca(placaEst);

            if (!v) {
                cout << "  [!] No se encontro ningun vehiculo registrado con la placa: " << placaEst << "\n";
            } else {
                cout << "\n  ========================================\n";
                cout << "  [VEHiCULO ENCONTRADO CON EXITO!]\n";
                cout << "  Placa registrada: " << v->getPlaca() << "\n";
                // Si agregaste marca, modelo o color a la clase Vehiculo en un futuro, los imprimes aquí.
                cout << "  ========================================\n";
            }
        }
        if (op != 6) {
            cout << "\n";
            system("pause");
        }
    } while (op != 6);
}

// ============================================================
//  FUNCION AUXILIAR: Pide y valida fecha para reserva
// ============================================================
bool pedirFechaReserva(int& dia, int& mes, int& anio) {
    time_t ahora = time(nullptr);
    tm* hoy = localtime(&ahora);
    int aHoy   = hoy->tm_year + 1900;
    int aLimite = aHoy + 1;

    // Lambda recursiva: bisiesto
    auto esBisiesto = [](auto& self, int a) -> bool {
        return (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
    };

    cout << "\n  --- Ingrese la fecha deseada ---\n";
    cout << "  (Anio permitido: " << aHoy << " - " << aLimite << ")\n";
    cout << "  NOTA: Solo se asignan turnos de Lunes a Viernes.\n";
    cout << "        Si cae fin de semana o feriado, se reasignara\n";
    cout << "        automaticamente al siguiente dia laborable.\n\n";

    anio = Validador::leerEntero(
        "    Anio  (" + to_string(aHoy) + "-" + to_string(aLimite) + "): ",
        aHoy, aLimite);

    mes = Validador::leerEntero("    Mes   (1-12): ", 1, 12);

    int diasMax = 31;
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) diasMax = 30;
    else if (mes == 2) diasMax = esBisiesto(esBisiesto, anio) ? 29 : 28;

    dia = Validador::leerEntero(
        "    Dia   (1-" + to_string(diasMax) + "): ", 1, diasMax);

    string errRango = GestorFechas::validarRangoFecha(dia, mes, anio);
    if (!errRango.empty()) {
        cout << "  [!] " << errRango << "\n";
        return false;
    }
    return true;
}

// ============================================================
//  MENU TURNOS / RESERVAS
// ============================================================
void menuReservas(ListaDoble& lr, ListaUsuarios& lu, ListaVehiculos& lv) {
    int op;
    string ced, placa;

    // Lambda recursiva: mapea 0-6 al nombre del dia de la semana
    auto nombreDia = [](auto& self, int w) -> string {
        if (w == 0) return "Domingo";
        if (w == 1) return "Lunes";
        if (w == 2) return "Martes";
        if (w == 3) return "Miercoles";
        if (w == 4) return "Jueves";
        if (w == 5) return "Viernes";
        return "Sabado";
    };

    do {
        system("cls");
        cout << "\n========== GESTION DE TURNOS ==========\n";
        cout << "1. Registrar Turno\n";
        cout << "2. Listar Turnos\n";
        cout << "3. Modificar Fecha de Turno\n";
        cout << "4. Cancelar Turno\n";
        cout << "5. Buscar Turno por Placa\n";
        cout << "6. Ordenar Turnos\n";
        cout << "7. Volver al Menu Principal\n";


        op = Validador::leerOpcionPorClic(2, 8);

        if (op == 1) {
            cout << "  CI del Propietario: ";
            cin >> ced;
            cin.ignore(10000, '\n');
            Usuario* u = lu.buscar(ced);
            if (!u) {
                cout << "  [!] Propietario no registrado.\n";
                continue;
            }

            cout << "  Placa del Vehiculo: ";
            cin >> placa;
            cin.ignore(10000, '\n');
            string placaEst = Validador::aMayusculas(placa);
            Vehiculo* v = lv.buscar(placaEst);
            if (!v) {
                cout << "  [!] Vehiculo no registrado.\n";
                continue;
            }
            if (lr.buscarPorPlaca(placaEst)) {
                cout << "  [!] Ese vehiculo ya tiene un turno activo.\n";
                continue;
            }

            int dia, mes, anio;
            if (!pedirFechaReserva(dia, mes, anio)) continue;

            int hIni, mIni, hFin, mFin;
            cout << "\n  --- HORARIO DEL TURNO ---\n";
            while (true) {
                hIni = Validador::leerEntero("  Hora de Inicio (8-16): ", 8, 16);
                mIni = Validador::leerEntero("  Minuto Inicio (0-59): ", 0, 59);
                
                hFin = Validador::leerEntero("  Hora de Fin (8-17): ", 8, 17);
                mFin = Validador::leerEntero("  Minuto Fin (0-59): ", 0, 59);
                
                int tIni = (hIni * 60) + mIni;
                int tFin = (hFin * 60) + mFin;
                
                if (tIni >= tFin) {
                    cout << "  [!] Error: La hora de inicio debe ser ANTES que la hora de fin.\n\n";
                } else {
                    break; // Intervalo lógico correcto
                }
            }

            // Validar si choca con otro turno
            if (lr.hayCruceDeHorarios(dia, mes, anio, hIni, mIni, hFin, mFin)) {
                cout << "\n  [!] HORARIO OCUPADO: El intervalo se cruza con otro turno asignado ese dia.\n";
                continue; // Reinicia el proceso
            }

            tm fecha = {0};
            fecha.tm_mday = dia;
            fecha.tm_mon  = mes - 1;
            fecha.tm_year = anio - 1900;
            fecha.tm_isdst = -1;

            string razon = GestorFechas::ajustarFechaLaborable(&fecha);
            if (!razon.empty()) {
                cout << "\n  [AVISO] " << razon << "\n";
                cout << "  [AVISO] Se reasigno al siguiente dia laborable.\n";
            }

            cout << "\n  [INFO] Turno asignado el "
                 << fecha.tm_mday << "/" << (fecha.tm_mon + 1) << "/" << (fecha.tm_year + 1900) 
                 << " de " << hIni << ":" << (mIni < 10 ? "0" : "") << mIni 
                 << " a " << hFin << ":" << (mFin < 10 ? "0" : "") << mFin << "\n";

            // Guardar con los nuevos parámetros
            lr.agregarReserva(new Reserva(u, v, fecha, hIni, mIni, hFin, mFin));
            cout << "  [OK] Turno registrado exitosamente.\n";
            
            // Guardar en disco
            GestorArchivos::guardarTodo(lu, lv, lr);
            // Generar el TXT de intervalos
            GestorArchivos::guardarHistorialIntervalos(lr);

        } else if (op == 2) {
            lr.mostrarReservas();

        } else if (op == 3) {
            cout << "  Placa del vehiculo a modificar: ";
            cin >> placa;
            cin.ignore(10000, '\n');
            string placaEst = Validador::aMayusculas(placa);
            Reserva* r = lr.buscarPorPlaca(placaEst);
            if (!r) {
                cout << "  [!] No se encontro turno para esa placa.\n";
                continue;
            }

            int dia, mes, anio;
            if (!pedirFechaReserva(dia, mes, anio)) continue;

            tm fecha = {0};
            fecha.tm_mday = dia;
            fecha.tm_mon  = mes - 1;
            fecha.tm_year = anio - 1900;

            string razon = GestorFechas::ajustarFechaLaborable(&fecha);
            if (!razon.empty()) {
                cout << "\n  [AVISO] " << razon << "\n";
                cout << "  [AVISO] Se reasigno al siguiente dia laborable.\n";
            }

            cout << "\n  [INFO] Nueva fecha: "
                 << nombreDia(nombreDia, fecha.tm_wday) << " "
                 << fecha.tm_mday << "/" << (fecha.tm_mon + 1)
                 << "/" << (fecha.tm_year + 1900) << "\n";

            r->setFechaAsignada(fecha);
            cout << "  [OK] Fecha actualizada correctamente.\n";
            GestorArchivos::guardarTodo(lu, lv, lr);

        } else if (op == 4) {
            cout << "  Placa del turno a cancelar: ";
            cin >> placa;
            cin.ignore(10000, '\n');
            if (lr.eliminarReserva(Validador::aMayusculas(placa))) {
                cout << "  [OK] Turno cancelado y liberado.\n";
                GestorArchivos::guardarTodo(lu, lv, lr);
            } else
                cout << "  [!] No se encontro turno para esa placa.\n";

        } else if (op == 5) {
            cout << "  Placa a buscar (Ej: HAD-123): ";
            cin >> placa;
            cin.ignore(10000, '\n');
            string placaEst = Validador::aMayusculas(placa);
            Reserva* r = lr.buscarPorPlaca(placaEst);
            if (!r) {
                cout << "  [!] No se encontro ningun turno para la placa: " << placaEst << "\n";
            } else {
                tm f = r->getFechaAsignada();
                string nombre = r->getUsuario()->getNombre();
                string apellido = r->getUsuario()->getApellido();
                char fechaStr[20];
                snprintf(fechaStr, sizeof(fechaStr), "%02d/%02d/%02d",
                         f.tm_mday, f.tm_mon + 1, (f.tm_year + 1900) % 100);
                cout << "\n  El vehiculo " << placaEst
                     << " tiene la revision vehicular el " << fechaStr
                     << " y es el propietario "
                     << nombre << " " << apellido << "\n";
            }
        } else if (op == 6) {
            system("cls");
            cout << "\n  Criterio de ordenamiento:\n";
            cout << "  1. Nombre del Propietario\n";
            cout << "  2. Placa del Vehiculo\n";
            cout << "  3. Cedula del Propietario\n";
            cout << "  4. Fecha del Turno\n";
            cout << "  5. Apellido del Propietario\n";
            cout << "  6. Cancelar y volver\n";

            int crit = Validador::leerOpcionPorClic(2, 7);

            if (crit >= 1 && crit <= 5) {
                ordenarListaInterno<Nodo>(lr.getCabeza(), crit);
                cout << "\n  [OK] Lista ordenada por el criterio seleccionado.\n\n";
                lr.mostrarReservas();
            } else {
                cout << "\n  [INFO] Ordenamiento cancelado.\n";
            }
        }
        if (op != 7) {
            cout << "\n";
            system("pause");
        }
    } while (op != 7);
}

// ============================================================
//  MAIN
// ============================================================
int main() {
    ListaUsuarios  masterUsuarios;
    ListaVehiculos masterVehiculos;
    ListaDoble     masterReservas;

    cout << "\n==========================================\n";
    cout << "   SISTEMA DE MATRICULACION VEHICULAR    \n";
    cout << "         ECUADOR - Turnos de Revision    \n";
    cout << "==========================================\n";

    // Cargar datos al inicio
    cout << "\n  Cargando datos guardados...\n";
    GestorArchivos::cargarTodo(masterUsuarios, masterVehiculos, masterReservas);
    cout << "  Carga completada.\n";

    int op;
    do {
        system("cls");

        cout << "\n==========================================\n";
        cout << "   SISTEMA DE MATRICULACION VEHICULAR    \n";
        cout << "==========================================\n";
        cout << "1. Gestionar Usuarios\n";
        cout << "2. Gestionar Vehiculos\n";
        cout << "3. Gestionar Turnos / Reservas\n";
        cout << "4. Cifrar Placa (Metodo Cesar)\n";
        cout << "5. Cifrado Digital de todas las Placas\n";
        cout << "6. Salir\n";


        op = Validador::leerOpcionPorClic(4, 9);
        //op = Validador::leerEntero("Opcion: ", 1, 6);

        switch (op) {
            case 1:
                menuUsuarios(masterUsuarios, masterReservas, masterVehiculos);
                break;
            case 2:
                menuVehiculos(masterVehiculos, masterReservas, masterUsuarios);
                break;
            case 3:
                menuReservas(masterReservas, masterUsuarios, masterVehiculos);
                break;
            case 4: {
                string placaIngresada;
                cout << "  Placa a cifrar (Ej: ABC-1234): ";
                cin >> placaIngresada;
                cin.ignore(10000, '\n');

                if (!Validador::validarPlaca(placaIngresada)) {
                    cout << "  [!] Placa invalida. Formato correcto: ABC-1234 o ABC-123\n";
                    break;
                }

                int desp = Validador::leerEntero("  Desplazamiento Cesar (1-25): ", 1, 25);
                string placaMay   = Validador::aMayusculas(placaIngresada);
                string placaCifrada = Validador::cifrarPlacaCesar(placaMay, desp);

                cout << "  Placa original : " << placaMay    << "\n";
                cout << "  Desplazamiento : " << desp         << "\n";
                cout << "  Placa cifrada  : " << placaCifrada << "\n";
                break;
            }
            case 5:
                GestorArchivos::guardarTodo(masterUsuarios, masterVehiculos, masterReservas);
                CifradoPlaca::cifrarDesdeArchivo("vehiculos.txt");
                break;
            case 6:
                cout << "\n  Hasta pronto.\n";
                break;
        }
    } while (op != 6);

    return 0;
}