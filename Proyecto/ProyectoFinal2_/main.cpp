#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include "ListaUsuarios.h"
#include "ListaVehiculos.h"
#include "ListaDoble.h"
#include "GestorFechas.h"
#include "GestorArchivos.h"
#include "Validador.h"

using namespace std;

// ============================================================
//  MENU USUARIOS
// ============================================================
void menuUsuarios(ListaUsuarios& lu, ListaDoble& lr) {
    int op;
    string ced;
    do {
        cout << "\n========== GESTION DE USUARIOS ==========\n";
        cout << "1. Registrar Usuario\n";
        cout << "2. Listar Usuarios\n";
        cout << "3. Modificar Usuario\n";
        cout << "4. Eliminar Usuario\n";
        cout << "5. Volver al Menu Principal\n";

        op = Validador::leerEntero("Opcion: ", 1, 5);

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

        } else if (op == 4) {
            cout << "  Cedula del usuario a eliminar: ";
            cin >> ced;
            cin.ignore(10000, '\n');
            lr.eliminarCascadaUsuario(ced);
            if (lu.eliminar(ced))
                cout << "  [OK] Usuario y sus turnos eliminados del sistema.\n";
            else
                cout << "  [!] Usuario no encontrado.\n";
        }
    } while (op != 5);
}

// ============================================================
//  MENU VEHICULOS
// ============================================================
void menuVehiculos(ListaVehiculos& lv, ListaDoble& lr) {
    int op;
    string placa, nuevaPlaca;
    do {
        cout << "\n========== GESTION DE VEHICULOS ==========\n";
        cout << "1. Registrar Vehiculo\n";
        cout << "2. Listar Vehiculos\n";
        cout << "3. Modificar Placa\n";
        cout << "4. Eliminar Vehiculo\n";
        cout << "5. Volver al Menu Principal\n";

        op = Validador::leerEntero("Opcion: ", 1, 5);

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

        } else if (op == 4) {
            cout << "  Placa a eliminar: ";
            cin >> placa;
            cin.ignore(10000, '\n');
            string placaEst = Validador::aMayusculas(placa);
            lr.eliminarCascadaVehiculo(placaEst);
            if (lv.eliminar(placaEst))
                cout << "  [OK] Vehiculo y su turno activo eliminados.\n";
            else
                cout << "  [!] Vehiculo no encontrado.\n";
        }
    } while (op != 5);
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
        cout << "\n========== GESTION DE TURNOS ==========\n";
        cout << "1. Registrar Turno\n";
        cout << "2. Listar Turnos\n";
        cout << "3. Modificar Fecha de Turno\n";
        cout << "4. Cancelar Turno\n";
        cout << "5. Volver al Menu Principal\n";

        op = Validador::leerEntero("Opcion: ", 1, 5);

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

            tm fecha = {0};
            fecha.tm_mday = dia;
            fecha.tm_mon  = mes - 1;
            fecha.tm_year = anio - 1900;

            string razon = GestorFechas::ajustarFechaLaborable(&fecha);
            if (!razon.empty()) {
                cout << "\n  [AVISO] " << razon << "\n";
                cout << "  [AVISO] Se reasigno al siguiente dia laborable.\n";
            }

            cout << "\n  [INFO] Turno asignado para: "
                 << nombreDia(nombreDia, fecha.tm_wday) << " "
                 << fecha.tm_mday << "/" << (fecha.tm_mon + 1)
                 << "/" << (fecha.tm_year + 1900) << "\n";

            lr.agregarReserva(new Reserva(u, v, fecha));
            cout << "  [OK] Turno registrado exitosamente.\n";

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

        } else if (op == 4) {
            cout << "  Placa del turno a cancelar: ";
            cin >> placa;
            cin.ignore(10000, '\n');
            if (lr.eliminarReserva(Validador::aMayusculas(placa)))
                cout << "  [OK] Turno cancelado y liberado.\n";
            else
                cout << "  [!] No se encontro turno para esa placa.\n";
        }
    } while (op != 5);
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
        cout << "\n==========================================\n";
        cout << "   SISTEMA DE MATRICULACION VEHICULAR    \n";
        cout << "==========================================\n";
        cout << "1. Gestionar Usuarios\n";
        cout << "2. Gestionar Vehiculos\n";
        cout << "3. Gestionar Turnos / Reservas\n";
        cout << "4. Guardar datos manualmente\n";
        cout << "5. Salir (guarda automaticamente)\n";
        op = Validador::leerEntero("Opcion: ", 1, 5);

        switch (op) {
            case 1:
                menuUsuarios(masterUsuarios, masterReservas);
                break;
            case 2:
                menuVehiculos(masterVehiculos, masterReservas);
                break;
            case 3:
                menuReservas(masterReservas, masterUsuarios, masterVehiculos);
                break;
            case 4:
                if (GestorArchivos::guardarTodo(masterUsuarios, masterVehiculos, masterReservas))
                    cout << "  [OK] Datos guardados en usuarios.txt, vehiculos.txt y reservas.txt\n";
                else
                    cout << "  [!] Hubo errores al guardar algunos archivos.\n";
                break;
            case 5:
                cout << "\n  Guardando datos antes de salir...\n";
                if (GestorArchivos::guardarTodo(masterUsuarios, masterVehiculos, masterReservas))
                    cout << "  [OK] Datos guardados correctamente. Hasta pronto.\n";
                else
                    cout << "  [!] Hubo errores al guardar. Revise permisos de escritura.\n";
                break;
        }
    } while (op != 5);

    return 0;
}
