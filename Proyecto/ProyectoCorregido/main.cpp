#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include "ListaUsuarios.h"
#include "ListaVehiculos.h"
#include "ListaDoble.h"
#include "GestorFechas.h"
#include "Validador.h"

using namespace std;

// ============================================================
//  MENU USUARIOS
// ============================================================
void menuUsuarios(ListaUsuarios& lu, ListaDoble& lr) {
    int op;
    string ced, nom, ape;
    do {
        cout << "\n========== GESTION DE USUARIOS ==========\n";
        cout << "1. Registrar Usuario\n";
        cout << "2. Listar Usuarios\n";
        cout << "3. Modificar Usuario\n";
        cout << "4. Eliminar Usuario\n";
        cout << "5. Volver al Menu Principal\n";

        op = Validador::leerEntero("Opcion: ", 1, 5);

        if (op == 1) {
            do {
                cout << "Ingrese Cedula Ecuatoriana (10 digitos): ";
                cin >> ced;
                if (!Validador::validarCedula(ced))
                    cout << "  [!] Cedula invalida (algoritmo Modulo 10 fallido).\n";
            } while (!Validador::validarCedula(ced));

            if (lu.buscar(ced)) {
                cout << "  [!] Ya existe un usuario registrado con esa cedula.\n";
                continue;
            }

            cin.ignore(10000, '\n');

            do {
                cout << "Ingrese Nombre: ";
                getline(cin, nom);
                if (!Validador::validarTexto(nom))
                    cout << "  [!] El nombre solo puede contener letras y espacios.\n";
            } while (!Validador::validarTexto(nom));

            do {
                cout << "Ingrese Apellido: ";
                getline(cin, ape);
                if (!Validador::validarTexto(ape))
                    cout << "  [!] El apellido solo puede contener letras y espacios.\n";
            } while (!Validador::validarTexto(ape));

            lu.crear(new Usuario(Validador::aMayusculas(nom),
                                 Validador::aMayusculas(ape), ced));
            cout << "  [OK] Usuario registrado exitosamente.\n";

        } else if (op == 2) {
            lu.reportar();

        } else if (op == 3) {
            cout << "Cedula del usuario a modificar: ";
            cin >> ced;
            if (!lu.buscar(ced)) {
                cout << "  [!] Usuario no encontrado.\n";
                continue;
            }
            cin.ignore(10000, '\n');
            do {
                cout << "Nuevo Nombre: ";
                getline(cin, nom);
            } while (!Validador::validarTexto(nom));
            do {
                cout << "Nuevo Apellido: ";
                getline(cin, ape);
            } while (!Validador::validarTexto(ape));

            lu.actualizar(ced, Validador::aMayusculas(nom),
                               Validador::aMayusculas(ape));
            cout << "  [OK] Usuario modificado con exito.\n";

        } else if (op == 4) {
            cout << "Cedula del usuario a eliminar: ";
            cin >> ced;
            lr.eliminarCascadaUsuario(ced);
            if (lu.eliminar(ced))
                cout << "  [OK] Usuario y sus reservas eliminados del sistema.\n";
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
                cout << "Ingrese Placa (Ej: ABC-1234): ";
                cin >> placa;
                if (!Validador::validarPlaca(placa))
                    cout << "  [!] Formato invalido o provincia no reconocida.\n";
            } while (!Validador::validarPlaca(placa));

            string placaEstandar = Validador::aMayusculas(placa);
            if (lv.buscar(placaEstandar)) {
                cout << "  [!] Este vehiculo ya esta registrado.\n";
                continue;
            }
            lv.crear(new Vehiculo(placaEstandar));
            cout << "  [OK] Vehiculo registrado: " << placaEstandar << "\n";

        } else if (op == 2) {
            lv.reportar();

        } else if (op == 3) {
            cout << "Placa actual del vehiculo: ";
            cin >> placa;
            string placaEstandar = Validador::aMayusculas(placa);
            if (!lv.buscar(placaEstandar)) {
                cout << "  [!] Vehiculo no encontrado.\n";
                continue;
            }
            do {
                cout << "Nueva Placa: ";
                cin >> nuevaPlaca;
                if (!Validador::validarPlaca(nuevaPlaca))
                    cout << "  [!] Formato o provincia invalida.\n";
            } while (!Validador::validarPlaca(nuevaPlaca));

            lv.actualizar(placaEstandar, Validador::aMayusculas(nuevaPlaca));
            cout << "  [OK] Placa actualizada.\n";

        } else if (op == 4) {
            cout << "Placa del vehiculo a eliminar: ";
            cin >> placa;
            string placaEstandar = Validador::aMayusculas(placa);
            lr.eliminarCascadaVehiculo(placaEstandar);
            if (lv.eliminar(placaEstandar))
                cout << "  [OK] Vehiculo y su reserva activa eliminados.\n";
            else
                cout << "  [!] Vehiculo no encontrado.\n";
        }
    } while (op != 5);
}

// ============================================================
//  FUNCION AUXILIAR: Pide y valida una fecha para reserva
//  Retorna true si se ingreso correctamente, false si el usuario
//  quiere cancelar (ingresa 0 en cualquier campo).
// ============================================================
bool pedirFechaReserva(int& dia, int& mes, int& anio) {

    // Obtener fecha actual y limite (1 anio adelante)
    time_t ahora = time(nullptr);
    tm* hoy = localtime(&ahora);
    int aHoy = hoy->tm_year + 1900;

    // Lambda recursiva: calcula si anio es bisiesto
    auto esBisiesto = [](auto& self, int a) -> bool {
        return (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
    };

    int aLimite = aHoy + 1;

    cout << "\n  --- Ingrese la fecha deseada ---\n";
    cout << "  (Anio permitido: " << aHoy << " - " << aLimite << ")\n";
    cout << "  NOTA: Los turnos se asignan solo de Lunes a Viernes.\n";
    cout << "        Si su fecha cae en fin de semana o feriado,\n";
    cout << "        se le asignara el siguiente dia laborable.\n\n";

    // Validar anio primero
    anio = Validador::leerEntero("    Anio  (" + to_string(aHoy) + "-" +
                                  to_string(aLimite) + "): ",
                                  aHoy, aLimite);

    mes = Validador::leerEntero("    Mes   (1-12): ", 1, 12);

    // Calcular dias maximos del mes/anio ingresado
    int diasMax = 31;
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) diasMax = 30;
    else if (mes == 2) {
        bool bisiesto = esBisiesto(esBisiesto, anio);
        diasMax = bisiesto ? 29 : 28;
    }

    dia = Validador::leerEntero("    Dia   (1-" + to_string(diasMax) + "): ",
                                 1, diasMax);

    // Validar rango completo (no pasado, no mas de 1 anio)
    string errRango = GestorFechas::validarRangoFecha(dia, mes, anio);
    if (!errRango.empty()) {
        cout << "  [!] " << errRango << "\n";
        return false;
    }

    return true;
}

// ============================================================
//  MENU RESERVAS / TURNOS
// ============================================================
void menuReservas(ListaDoble& lr, ListaUsuarios& lu, ListaVehiculos& lv) {
    int op;
    string ced, placa;

    // Nombres de dias de la semana (sin arreglos fuera de lambdas)
    // Se usan inline mediante lambda recursiva que mapea 0-6 a nombre
    auto nombreDia = [](auto& self, int wday) -> string {
        if (wday == 0) return "Domingo";
        if (wday == 1) return "Lunes";
        if (wday == 2) return "Martes";
        if (wday == 3) return "Miercoles";
        if (wday == 4) return "Jueves";
        if (wday == 5) return "Viernes";
        return "Sabado";
    };

    do {
        cout << "\n========== GESTION DE TURNOS (MATRICULACION) ==========\n";
        cout << "1. Registrar Turno\n";
        cout << "2. Listar Turnos\n";
        cout << "3. Modificar Fecha de Turno\n";
        cout << "4. Cancelar Turno\n";
        cout << "5. Volver al Menu Principal\n";

        op = Validador::leerEntero("Opcion: ", 1, 5);

        if (op == 1) {
            // Verificar usuario
            cout << "Ingrese CI del Propietario: ";
            cin >> ced;
            Usuario* u = lu.buscar(ced);
            if (!u) {
                cout << "  [!] Propietario no registrado. Registrelo primero en Usuarios.\n";
                continue;
            }

            // Verificar vehiculo
            cout << "Ingrese Placa del Vehiculo: ";
            cin >> placa;
            string placaEstandar = Validador::aMayusculas(placa);
            Vehiculo* v = lv.buscar(placaEstandar);
            if (!v) {
                cout << "  [!] Vehiculo no registrado. Registrelo primero en Vehiculos.\n";
                continue;
            }

            if (lr.buscarPorPlaca(placaEstandar)) {
                cout << "  [!] Ese vehiculo ya tiene un turno activo registrado.\n";
                continue;
            }

            // Pedir fecha
            int dia, mes, anio;
            if (!pedirFechaReserva(dia, mes, anio)) continue;

            // Construir tm y ajustar
            tm fecha = {0};
            fecha.tm_mday = dia;
            fecha.tm_mon  = mes - 1;
            fecha.tm_year = anio - 1900;

            string razonAjuste = GestorFechas::ajustarFechaLaborable(&fecha);

            // Si hubo ajuste, informar al usuario
            if (!razonAjuste.empty()) {
                cout << "\n  [AVISO] " << razonAjuste << "\n";
                cout << "  [AVISO] El turno fue reasignado al siguiente dia laborable.\n";
            }

            cout << "\n  [INFO] Turno asignado para: "
                 << nombreDia(nombreDia, fecha.tm_wday) << " "
                 << fecha.tm_mday << "/"
                 << (fecha.tm_mon + 1) << "/"
                 << (fecha.tm_year + 1900) << "\n";

            lr.agregarReserva(new Reserva(u, v, fecha));
            cout << "  [OK] Turno de matriculacion registrado exitosamente.\n";

        } else if (op == 2) {
            lr.mostrarReservas();

        } else if (op == 3) {
            cout << "Placa del vehiculo a modificar: ";
            cin >> placa;
            string placaEstandar = Validador::aMayusculas(placa);
            Reserva* r = lr.buscarPorPlaca(placaEstandar);
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

            string razonAjuste = GestorFechas::ajustarFechaLaborable(&fecha);

            if (!razonAjuste.empty()) {
                cout << "\n  [AVISO] " << razonAjuste << "\n";
                cout << "  [AVISO] El turno fue reasignado al siguiente dia laborable.\n";
            }

            cout << "\n  [INFO] Nueva fecha de turno: "
                 << nombreDia(nombreDia, fecha.tm_wday) << " "
                 << fecha.tm_mday << "/"
                 << (fecha.tm_mon + 1) << "/"
                 << (fecha.tm_year + 1900) << "\n";

            r->setFechaAsignada(fecha);
            cout << "  [OK] Fecha de turno actualizada correctamente.\n";

        } else if (op == 4) {
            cout << "Placa del vehiculo a cancelar: ";
            cin >> placa;
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

    int op;
    do {
        cout << "\n==========================================\n";
        cout << "   SISTEMA DE MATRICULACION VEHICULAR    \n";
        cout << "         ECUADOR - Turnos de Revision    \n";
        cout << "==========================================\n";
        cout << "1. Gestionar Usuarios\n";
        cout << "2. Gestionar Vehiculos\n";
        cout << "3. Gestionar Turnos / Reservas\n";
        cout << "4. Salir\n";
        op = Validador::leerEntero("Opcion: ", 1, 4);

        switch (op) {
            case 1: menuUsuarios(masterUsuarios, masterReservas);                break;
            case 2: menuVehiculos(masterVehiculos, masterReservas);              break;
            case 3: menuReservas(masterReservas, masterUsuarios, masterVehiculos); break;
            case 4: cout << "\nCerrando sistema. Liberando memoria...\n";        break;
        }
    } while (op != 4);

    return 0;
}
