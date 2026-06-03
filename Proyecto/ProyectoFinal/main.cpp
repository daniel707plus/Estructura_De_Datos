#include <iostream>
#include <string>
#include "Validaciones.h"
#include "ListaUsuarios.h"
#include "ListaVehiculos.h"
#include "ListaDoble.h"
#include "GestorFechas.h"

using namespace std;

// ============================================================
//  MENU USUARIOS
// ============================================================
void menuUsuarios(ListaUsuarios& lu, ListaDoble& lr) {
    int op;
    do {
        cout << "\n========== GESTION DE USUARIOS ==========\n";
        cout << "1. Registrar usuario\n";
        cout << "2. Listar usuarios\n";
        cout << "3. Modificar usuario\n";
        cout << "4. Eliminar usuario\n";
        cout << "5. Volver al menu principal\n";
        op = leerEnteroEnRango("Opcion: ", 1, 5);

        if (op == 1) {
            // -- Registrar --
            string ced = pedirCedula("  Cedula (10 digitos): ");
            if (lu.buscar(ced)) {
                cout << "  [!] Ya existe un usuario con esa cedula.\n";
                continue;
            }
            string nom = leerSoloLetras("  Nombre: ");
            string ape = leerSoloLetras("  Apellido: ");
            lu.crear(new Usuario(nom, ape, ced));
            cout << "  [OK] Usuario registrado con exito.\n";

        } else if (op == 2) {
            lu.reportar();

        } else if (op == 3) {
            // -- Modificar --
            string ced = pedirCedula("  Cedula del usuario a modificar: ");
            if (!lu.buscar(ced)) { cout << "  [!] Usuario no encontrado.\n"; continue; }
            string nom = leerSoloLetras("  Nuevo Nombre: ");
            string ape = leerSoloLetras("  Nuevo Apellido: ");
            lu.actualizar(ced, nom, ape);
            cout << "  [OK] Datos actualizados.\n";

        } else if (op == 4) {
            // -- Eliminar --
            string ced = pedirCedula("  Cedula del usuario a eliminar: ");
            lr.eliminarCascadaUsuario(ced); // Cancela sus reservas primero
            if (lu.eliminar(ced)) cout << "  [OK] Usuario eliminado del sistema.\n";
            else cout << "  [!] Usuario no encontrado.\n";
        }
    } while (op != 5);
}

// ============================================================
//  MENU VEHICULOS
// ============================================================
void menuVehiculos(ListaVehiculos& lv, ListaDoble& lr) {
    int op;
    do {
        cout << "\n========== GESTION DE VEHICULOS ==========\n";
        cout << "1. Registrar vehiculo\n";
        cout << "2. Listar vehiculos\n";
        cout << "3. Modificar placa\n";
        cout << "4. Eliminar vehiculo\n";
        cout << "5. Volver al menu principal\n";
        op = leerEnteroEnRango("Opcion: ", 1, 5);

        if (op == 1) {
            // -- Registrar --
            string placa = pedirPlaca("  Placa (ej: ABC-1234): ");
            if (lv.buscar(placa)) {
                cout << "  [!] Ya existe un vehiculo con esa placa.\n";
                continue;
            }
            lv.crear(new Vehiculo(placa));
            cout << "  [OK] Vehiculo registrado: " << placa << "\n";

        } else if (op == 2) {
            lv.reportar();

        } else if (op == 3) {
            // -- Modificar placa --
            string placa = pedirPlaca("  Placa actual: ");
            if (!lv.buscar(placa)) { cout << "  [!] Vehiculo no encontrado.\n"; continue; }
            string nueva = pedirPlaca("  Nueva Placa: ");
            if (lv.buscar(nueva)) { cout << "  [!] Esa placa ya esta en uso.\n"; continue; }
            lv.actualizar(placa, nueva);
            cout << "  [OK] Placa actualizada a: " << nueva << "\n";

        } else if (op == 4) {
            // -- Eliminar --
            string placa = pedirPlaca("  Placa a eliminar: ");
            lr.eliminarCascadaVehiculo(placa); // Cancela reserva ligada
            if (lv.eliminar(placa)) cout << "  [OK] Vehiculo eliminado.\n";
            else cout << "  [!] Vehiculo no encontrado.\n";
        }
    } while (op != 5);
}

// ============================================================
//  MENU RESERVAS / TURNOS
// ============================================================
void menuReservas(ListaDoble& lr, ListaUsuarios& lu, ListaVehiculos& lv) {
    int op;
    do {
        cout << "\n========== GESTION DE TURNOS ==========\n";
        cout << "1. Crear Reserva de turno\n";
        cout << "2. Listar Reservas\n";
        cout << "3. Modificar fecha de Reserva\n";
        cout << "4. Cancelar Reserva\n";
        cout << "5. Volver al menu principal\n";
        op = leerEnteroEnRango("Opcion: ", 1, 5);

        if (op == 1) {
            // -- Crear reserva --
            string ced = pedirCedula("  CI del Propietario: ");
            Usuario* u = lu.buscar(ced);
            if (!u) { cout << "  [!] Propietario no registrado. Registrelo primero en Usuarios.\n"; continue; }

            string placa = pedirPlaca("  Placa del Vehiculo: ");
            Vehiculo* v = lv.buscar(placa);
            if (!v) { cout << "  [!] Vehiculo no registrado. Registrelo primero en Vehiculos.\n"; continue; }

            if (lr.buscarPorPlaca(placa)) {
                cout << "  [!] Ese vehiculo ya tiene una reserva activa.\n"; continue;
            }

            cout << "  Ingrese la fecha deseada:\n";
            int dia = leerEnteroEnRango("    Dia   (1-31): ", 1, 31);
            int mes = leerEnteroEnRango("    Mes   (1-12): ", 1, 12);
            int anio = leerEnteroEnRango("    Anio  (ej: 2025): ", 2000, 2100);

            tm fecha = {0};
            fecha.tm_mday  = dia;
            fecha.tm_mon   = mes - 1;
            fecha.tm_year  = anio - 1900;

            GestorFechas::ajustarFechaLaborable(&fecha);

            const char* diasSemana[] = {"Domingo","Lunes","Martes","Miercoles","Jueves","Viernes","Sabado"};
            cout << "  [INFO] Turno asignado para: "
                 << diasSemana[fecha.tm_wday] << " "
                 << fecha.tm_mday << "/" << (fecha.tm_mon+1) << "/" << (fecha.tm_year+1900) << "\n";

            lr.agregarReserva(new Reserva(u, v, fecha));
            cout << "  [OK] Reserva de turno registrada exitosamente.\n";

        } else if (op == 2) {
            lr.mostrarReservas();

        } else if (op == 3) {
            // -- Modificar fecha --
            string placa = pedirPlaca("  Placa del vehiculo de la reserva: ");
            Reserva* r = lr.buscarPorPlaca(placa);
            if (!r) { cout << "  [!] No se encontro reserva para esa placa.\n"; continue; }

            cout << "  Nueva fecha:\n";
            int dia  = leerEnteroEnRango("    Dia   (1-31): ", 1, 31);
            int mes  = leerEnteroEnRango("    Mes   (1-12): ", 1, 12);
            int anio = leerEnteroEnRango("    Anio  (ej: 2025): ", 2000, 2100);

            tm fecha = {0};
            fecha.tm_mday = dia; fecha.tm_mon = mes-1; fecha.tm_year = anio-1900;
            GestorFechas::ajustarFechaLaborable(&fecha);

            const char* diasSemana[] = {"Domingo","Lunes","Martes","Miercoles","Jueves","Viernes","Sabado"};
            cout << "  [INFO] Nueva fecha de turno: "
                 << diasSemana[fecha.tm_wday] << " "
                 << fecha.tm_mday << "/" << (fecha.tm_mon+1) << "/" << (fecha.tm_year+1900) << "\n";

            r->setFechaAsignada(fecha);
            cout << "  [OK] Fecha de reserva actualizada.\n";

        } else if (op == 4) {
            // -- Cancelar reserva --
            string placa = pedirPlaca("  Placa de la reserva a cancelar: ");
            if (lr.eliminarReserva(placa)) cout << "  [OK] Reserva cancelada.\n";
            else cout << "  [!] No se encontro reserva para esa placa.\n";
        }
    } while (op != 5);
}

// ============================================================
//  MAIN
// ============================================================
int main() {
    // Limpiar buffer de entrada al inicio
    cin.ignore();

    ListaUsuarios  masterUsuarios;
    ListaVehiculos masterVehiculos;
    ListaDoble     masterReservas;

    int op;
    do {
        cout << "\n==========================================\n";
        cout << "   SISTEMA MATRICULACION VEHICULAR       \n";
        cout << "         ECUADOR - Registro Turnos       \n";
        cout << "==========================================\n";
        cout << "1. Gestionar Usuarios\n";
        cout << "2. Gestionar Vehiculos\n";
        cout << "3. Gestionar Reservas / Turnos\n";
        cout << "4. Salir\n";
        op = leerEnteroEnRango("Opcion: ", 1, 4);

        switch (op) {
            case 1: menuUsuarios(masterUsuarios, masterReservas);           break;
            case 2: menuVehiculos(masterVehiculos, masterReservas);         break;
            case 3: menuReservas(masterReservas, masterUsuarios, masterVehiculos); break;
            case 4: cout << "\nSaliendo del sistema. Hasta pronto.\n";      break;
        }
    } while (op != 4);

    return 0;
}
