#include <iostream>
#include <string>
#include "ListaUsuarios.h"
#include "ListaVehiculos.h"
#include "ListaDoble.h"
#include "GestorFechas.h"
#include "Validador.h" 

using namespace std;

void menuUsuarios(ListaUsuarios& lu, ListaDoble& lr) {
    int op; 
    string ced, nom, ape;
    do {
        cout << "\n--- CRUD USUARIOS ---\n";
        cout << "1. Registrar Usuario\n";
        cout << "2. Listar Usuarios\n";
        cout << "3. Modificar Usuario\n";
        cout << "4. Eliminar Usuario\n";
        cout << "5. Volver al Menu Principal\n";
        
        // Uso de leerEntero para evitar que las letras rompan el menú
        op = Validador::leerEntero("Opcion: ", 1, 5);

        if (op == 1) {
            // 1. Validar Cédula antes de registrar
            do {
                cout << "Ingrese Cedula Ecuatoriana (10 digitos): ";
                cin >> ced;
                if (!Validador::validarCedula(ced)) {
                    cout << "Error: La cedula no es valida en Ecuador (Algoritmo Modulo 10 fallido).\n";
                }
            } while (!Validador::validarCedula(ced));

            if (lu.buscar(ced)) { 
                cout << "Error de Duplicidad: Ya existe un usuario registrado con esa cedula.\n"; 
                continue; 
            }

            cin.ignore(10000, '\n'); // Limpiar el buffer antes de usar getline
            
            // 2. Validar Nombre (Solo letras y espacios)
            do {
                cout << "Ingrese Nombre: ";
                getline(cin, nom);
                if (!Validador::validarTexto(nom)) {
                    cout << "Error: El nombre solo puede contener letras y espacios.\n";
                }
            } while (!Validador::validarTexto(nom));
            
            // 3. Validar Apellido (Solo letras y espacios)
            do {
                cout << "Ingrese Apellido: ";
                getline(cin, ape);
                if (!Validador::validarTexto(ape)) {
                    cout << "Error: El apellido solo puede contener letras y espacios.\n";
                }
            } while (!Validador::validarTexto(ape));

            // Guardamos todo estandarizado en mayúsculas mediante punteros
            lu.crear(new Usuario(Validador::aMayusculas(nom), Validador::aMayusculas(ape), ced));
            cout << ">>> Usuario registrado exitosamente.\n";

        } else if (op == 2) { 
            lu.reportar(); 
        } else if (op == 3) {
            cout << "Ingrese la Cedula del usuario a modificar: "; 
            cin >> ced;
            if (!lu.buscar(ced)) { 
                cout << "Error: Usuario no encontrado.\n"; 
                continue; 
            }
            
            cin.ignore(10000, '\n');
            do {
                cout << "Nuevo Nombre: "; getline(cin, nom);
            } while (!Validador::validarTexto(nom));
            
            do {
                cout << "Nuevo Apellido: "; getline(cin, ape);
            } while (!Validador::validarTexto(ape));

            lu.actualizar(ced, Validador::aMayusculas(nom), Validador::aMayusculas(ape)); 
            cout << ">>> Usuario modificado con exito.\n";

        } else if (op == 4) {
            cout << "Ingrese la Cedula del usuario a eliminar: "; 
            cin >> ced;
            
            // Eliminación en cascada para evitar punteros huérfanos en las reservas
            lr.eliminarCascadaUsuario(ced); 
            
            if (lu.eliminar(ced)) {
                cout << ">>> Usuario y sus reservas asociadas eliminados del sistema.\n";
            } else {
                cout << "Error: Usuario no encontrado.\n";
            }
        }
    } while (op != 5);
}

void menuVehiculos(ListaVehiculos& lv, ListaDoble& lr) {
    int op; 
    string placa, nuevaPlaca;
    do {
        cout << "\n--- CRUD VEHICULOS ---\n";
        cout << "1. Registrar Vehiculo\n";
        cout << "2. Listar Vehiculos\n";
        cout << "3. Modificar Placa\n";
        cout << "4. Eliminar Vehiculo\n";
        cout << "5. Volver al Menu Principal\n";
        
        op = Validador::leerEntero("Opcion: ", 1, 5);

        if (op == 1) {
            // Validar Estructura y Provincia de la Placa
            do {
                cout << "Ingrese Placa (Ej: ABC-1234 o ABC1234): ";
                cin >> placa;
                if (!Validador::validarPlaca(placa)) {
                    cout << "Error: Formato invalido o la primera letra no pertenece a una provincia real de Ecuador.\n";
                }
            } while (!Validador::validarPlaca(placa));

            // Estandarizar antes de buscar para evitar que "abc-1234" escape al filtro
            string placaEstandar = Validador::aMayusculas(placa);
            if (lv.buscar(placaEstandar)) { 
                cout << "Error de Duplicidad: Este vehiculo ya se encuentra registrado.\n"; 
                continue; 
            }

            lv.crear(new Vehiculo(placaEstandar)); 
            cout << ">>> Vehiculo registrado exitosamente.\n";

        } else if (op == 2) { 
            lv.reportar(); 
        } else if (op == 3) {
            cout << "Ingrese Placa actual del vehiculo: "; 
            cin >> placa;
            string placaEstandar = Validador::aMayusculas(placa);
            
            if (!lv.buscar(placaEstandar)) { 
                cout << "Error: Vehiculo no encontrado.\n"; 
                continue; 
            }
            
            do {
                cout << "Ingrese Nueva Placa: ";
                cin >> nuevaPlaca;
                if (!Validador::validarPlaca(nuevaPlaca)) {
                    cout << "Error: Formato o provincia invalida.\n";
                }
            } while (!Validador::validarPlaca(nuevaPlaca));

            lv.actualizar(placaEstandar, Validador::aMayusculas(nuevaPlaca)); 
            cout << ">>> Placa actualizada con exito.\n";

        } else if (op == 4) {
            cout << "Ingrese Placa del vehiculo a eliminar: "; 
            cin >> placa;
            string placaEstandar = Validador::aMayusculas(placa);
            
            lr.eliminarCascadaVehiculo(placaEstandar);
            if (lv.eliminar(placaEstandar)) {
                cout << ">>> Vehiculo y su reserva activa fueron removidos.\n";
            } else {
                cout << "Error: Vehiculo no encontrado.\n";
            }
        }
    } while (op != 5);
}

void menuReservas(ListaDoble& lr, ListaUsuarios& lu, ListaVehiculos& lv) {
    int op, d, m, a; 
    string ced, placa;
    do {
        cout << "\n--- CRUD RESERVAS ---\n";
        cout << "1. Registrar Nueva Reserva\n";
        cout << "2. Mostrar Historial de Reservas\n";
        cout << "3. Modificar Fecha de Turno\n";
        cout << "4. Cancelar Turno (Eliminar)\n";
        cout << "5. Volver al Menu Principal\n";
        
        op = Validador::leerEntero("Opcion: ", 1, 5);

        if (op == 1) {
            // 1. Validar que el cliente exista en la lista maestra
            cout << "Ingrese CI del Cliente: "; 
            cin >> ced;
            Usuario* u = lu.buscar(ced);
            if (!u) { 
                cout << "Error Relacional: El usuario no existe en la base de datos. Registrelo primero.\n"; 
                continue; 
            }
            
            // 2. Validar que el vehículo exista en la lista maestra
            cout << "Ingrese Placa del Vehiculo: "; 
            cin >> placa;
            string placaEstandar = Validador::aMayusculas(placa);
            Vehiculo* v = lv.buscar(placaEstandar);
            if (!v) { 
                cout << "Error Relacional: El vehiculo no existe. Registrelo primero.\n"; 
                continue; 
            }
            
            // 3. Validar que el vehículo no tenga ya un turno asignado
            if (lr.buscarPorPlaca(placaEstandar)) { 
                cout << "Error Logico: Este vehiculo ya cuenta con una reserva de revision activa.\n"; 
                continue; 
            }

            // 4. Captura e inserción segura de fechas sin riesgo de datos basura o desbordamientos
            cout << "\n--- Calendario de Asignacion de Turnos ---\n";
            d = Validador::leerEntero("Ingrese Dia (1-31): ", 1, 31);
            m = Validador::leerEntero("Ingrese Mes (1-12): ", 1, 12);
            a = Validador::leerEntero("Ingrese Anio (2026-2030): ", 2026, 2030);

            // Validación lógica manual complementaria (ej: 31 de noviembre)
            int diasMax = 31;
            if (m == 4 || m == 6 || m == 9 || m == 11) diasMax = 30;
            else if (m == 2) {
                bool bisiesto = (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
                diasMax = bisiesto ? 29 : 28;
            }

            if (d > diasMax) {
                cout << "Error Cronologico: El mes " << m << " en el anio " << a << " solo posee " << diasMax << " dias.\n";
                continue;
            }

            tm fecha = {0}; 
            fecha.tm_mday = d; 
            fecha.tm_mon = m - 1; 
            fecha.tm_year = a - 1900;
            
            // El Gestor procesa fines de semana y feriados con la Ley de Traslados de Ecuador
            GestorFechas::ajustarFechaLaborable(&fecha); 
            
            lr.agregarReserva(new Reserva(u, v, fecha));
            cout << ">>> Reserva agendada exitosamente.\n";

        } else if (op == 2) { 
            lr.mostrarReservas(); 
        } else if (op == 3) {
            cout << "Ingrese la Placa vinculada a la reserva: "; 
            cin >> placa;
            string placaEstandar = Validador::aMayusculas(placa);
            Reserva* r = lr.buscarPorPlaca(placaEstandar);
            if (!r) { 
                cout << "Error: Reserva no encontrada.\n"; 
                continue; 
            }

            cout << "\n--- Nueva Fecha del Turno ---\n";
            d = Validador::leerEntero("Nuevo Dia (1-31): ", 1, 31);
            m = Validador::leerEntero("Nuevo Mes (1-12): ", 1, 12);
            a = Validador::leerEntero("Nuevo Anio (2026-2030): ", 2026, 2030);

            tm fecha = {0}; 
            fecha.tm_mday = d; 
            fecha.tm_mon = m - 1; 
            fecha.tm_year = a - 1900;
            
            GestorFechas::ajustarFechaLaborable(&fecha);
            r->setFechaAsignada(fecha);
            cout << ">>> Fecha de control actualizada correctamente.\n";

        } else if (op == 4) {
            cout << "Ingrese Placa del vehiculo para cancelar la reserva: "; 
            cin >> placa;
            if (lr.eliminarReserva(Validador::aMayusculas(placa))) {
                cout << ">>> Reserva eliminada y turno liberado.\n";
            } else {
                cout << "Error: Reserva no encontrada.\n";
            }
        }
    } while (op != 5);
}

int main() {
    ListaUsuarios masterUsuarios;
    ListaVehiculos masterVehiculos;
    ListaDoble masterReservas;
    
    int opcionPrincipal;
    do {
        cout << "\n=========================================\n";
        cout << "  SISTEMA DE REVISION VEHICULAR ECUADOR  \n";
        cout << "=========================================\n";
        cout << "1. Gestionar Usuarios (CRUD)\n";
        cout << "2. Gestionar Vehiculos (CRUD)\n";
        cout << "3. Gestionar Reservas (CRUD)\n";
        cout << "4. Salir del Sistema\n";
        
        opcionPrincipal = Validador::leerEntero("Opcion: ", 1, 4);

        switch(opcionPrincipal) {
            case 1: menuUsuarios(masterUsuarios, masterReservas); break;
            case 2: menuVehiculos(masterVehiculos, masterReservas); break;
            case 3: menuReservas(masterReservas, masterUsuarios, masterVehiculos); break;
            case 4: cout << "Cerrando el sistema... Liberando estructuras de memoria en cadena.\n"; break;
        }
    } while(opcionPrincipal != 4);

    return 0;
}