#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <vector>
#include <cctype>
#include <windows.h>   // ReadConsoleInput, MOUSE_EVENT
#include "ListaUsuarios.h"
#include "ListaVehiculos.h"
#include "ListaDoble.h"
#include "GestorFechas.h"
#include "GestorArchivos.h"
#include "Validador.h"

using namespace std;

// ============================================================
//  UTILIDADES DE CONSOLA
// ============================================================
void cls() { system("cls"); }

// Mueve el cursor a (col, fila)
void gotoxy(int x, int y) {
    COORD c; c.X = (SHORT)x; c.Y = (SHORT)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Activa color: 0A=verde, 0E=amarillo, 0F=blanco, 4F=blanco-sobre-rojo, etc.
void setColor(WORD attr) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
}
void resetColor() { setColor(0x0F); }

// Oculta/muestra cursor
void hideCursor() {
    CONSOLE_CURSOR_INFO ci; ci.dwSize = 1; ci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}
void showCursor() {
    CONSOLE_CURSOR_INFO ci; ci.dwSize = 10; ci.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}

// ============================================================
//  MENU SOLO CON MOUSE (click izquierdo)
//  Dibuja opciones y espera un click. Devuelve el indice (1-based).
// ============================================================
int menuMouse(const string& titulo, const vector<string>& opciones) {

    // Habilitar eventos de mouse en la consola
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD modoAnterior;
    GetConsoleMode(hIn, &modoAnterior);
    SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    hideCursor();

    // Coordenadas donde se dibuja cada opcion
    const int COL_TEXTO = 6;
    const int FILA_INI  = 5;
    const int ALTO_ITEM = 2;   // lineas por opcion (separacion)

    int total = (int)opciones.size();
    vector<int> filasOpciones(total);
    for (int i = 0; i < total; i++)
        filasOpciones[i] = FILA_INI + i * ALTO_ITEM;

    // Dibuja el menu completo
    auto dibujar = [&]() {
        cls();
        setColor(0x0B); // cyan
        cout << "\n";
        cout << "  ==============================================\n";
        cout << "  " << titulo << "\n";
        cout << "  ==============================================\n\n";

        for (int i = 0; i < total; i++) {
            gotoxy(2, filasOpciones[i]);
            setColor(0x0E); // amarillo
            cout << "  [ " << (i + 1) << " ]  ";
            setColor(0x0F); // blanco
            cout << opciones[i];
        }

        gotoxy(2, FILA_INI + total * ALTO_ITEM + 1);
        setColor(0x08); // gris
        cout << "  Haz CLICK sobre la opcion deseada";
        resetColor();
    };

    dibujar();

    // Bucle de espera de click
    while (true) {
        INPUT_RECORD ir;
        DWORD leidos;
        ReadConsoleInput(hIn, &ir, 1, &leidos);

        if (ir.EventType == MOUSE_EVENT) {
            MOUSE_EVENT_RECORD& me = ir.Event.MouseEvent;

            // Solo click izquierdo (boton presionado)
            if (me.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
                int fila = me.dwMousePosition.Y;
                int col  = me.dwMousePosition.X;

                for (int i = 0; i < total; i++) {
                    // Detecta si el click cayo en la fila de esa opcion
                    if (fila == filasOpciones[i] && col >= 2) {
                        // Resalta la opcion clickeada
                        gotoxy(2, filasOpciones[i]);
                        setColor(0x2F); // negro sobre verde
                        cout << "  [ " << (i + 1) << " ]  " << opciones[i] << "   ";
                        resetColor();
                        Sleep(180); // pequeña pausa visual

                        // Restaurar modo consola
                        SetConsoleMode(hIn, modoAnterior);
                        showCursor();
                        return i + 1;
                    }
                }
            }
        }
    }
}

// ============================================================
//  PICO Y PLACA
// ============================================================
bool tienePicoYPlaca(const string& placa, int diaSemana) {
    int ud = -1;
    for (int i = (int)placa.size()-1; i >= 0; i--)
        if (isdigit(placa[i])) { ud = placa[i]-'0'; break; }
    if (ud < 0) return false;
    switch (diaSemana) {
        case 1: return (ud==1||ud==2);
        case 2: return (ud==3||ud==4);
        case 3: return (ud==5||ud==6);
        case 4: return (ud==7||ud==8);
        case 5: return (ud==9||ud==0);
        default: return false;
    }
}
string diaPicoYPlaca(int ud) {
    switch(ud){
        case 1:case 2: return "Lunes";
        case 3:case 4: return "Martes";
        case 5:case 6: return "Miercoles";
        case 7:case 8: return "Jueves";
        default:       return "Viernes";
    }
}

bool slotOcupado(ListaDoble& lr, int dia, int mes, int anio, int hora) {
    Nodo* n = lr.getCabeza();
    while (n) {
        Reserva* r = n->getReserva();
        tm f = r->getFechaAsignada();
        if (f.tm_mday==dia && (f.tm_mon+1)==mes
            && (f.tm_year+1900)==anio && r->getHoraAsignada()==hora)
            return true;
        n = n->getSiguiente();
    }
    return false;
}

int elegirHora(ListaDoble& lr, int dia, int mes, int anio) {
    vector<int> disponibles;
    for (int h = 8; h <= 16; h++)
        if (!slotOcupado(lr, dia, mes, anio, h))
            disponibles.push_back(h);
    if (disponibles.empty()) {
        cout << "  [!] No hay turnos disponibles para esa fecha.\n";
        return -1;
    }
    vector<string> ops;
    for (int h : disponibles) ops.push_back(to_string(h) + ":00");
    int sel = menuMouse("SELECCIONE HORA", ops);
    return disponibles[sel-1];
}

bool pedirFechaReserva(int& dia, int& mes, int& anio) {
    time_t ahora = time(nullptr);
    tm* hoy = localtime(&ahora);
    int aHoy = hoy->tm_year+1900, aLim = aHoy+1;
    auto bisiesto = [](auto& s, int a)->bool{
        return (a%4==0&&a%100!=0)||(a%400==0);
    };
    cout << "\n  --- Ingrese la fecha deseada ---\n";
    cout << "  (Anio: " << aHoy << "-" << aLim << ")  Solo Lun-Vie.\n\n";
    anio = Validador::leerEntero("    Anio: ", aHoy, aLim);
    mes  = Validador::leerEntero("    Mes (1-12): ", 1, 12);
    int dmax = 31;
    if (mes==4||mes==6||mes==9||mes==11) dmax=30;
    else if (mes==2) dmax=bisiesto(bisiesto,anio)?29:28;
    dia = Validador::leerEntero("    Dia (1-"+to_string(dmax)+"): ", 1, dmax);
    string err = GestorFechas::validarRangoFecha(dia, mes, anio);
    if (!err.empty()) { cout << "  [!] " << err << "\n"; return false; }
    return true;
}

// ============================================================
//  MENU USUARIOS
// ============================================================
void menuUsuarios(ListaUsuarios& lu, ListaDoble& lr, ListaVehiculos& lv) {
    vector<string> ops = {
        "Registrar Usuario",
        "Listar Usuarios",
        "Modificar Usuario",
        "Eliminar Usuario",
        "Ordenamiento por Intercambio (animacion)",
        "Buscar Usuario por CI  [try/catch]",
        "Volver al Menu Principal"
    };
    string ced;
    int op;
    do {
        op = menuMouse("GESTION DE USUARIOS", ops);
        cls();

        if (op == 1) {
            cout << "\n--- REGISTRAR USUARIO ---\n";
            do {
                cout << "  Cedula (10 digitos): ";
                cin >> ced; cin.ignore(10000,'\n');
                if (!Validador::validarCedula(ced))
                    cout << "  [!] Cedula invalida.\n";
            } while (!Validador::validarCedula(ced));
            if (lu.buscar(ced)) {
                cout << "  [!] Ya existe un usuario con esa cedula.\n";
            } else {
                string nom = Validador::leerTextoValido("  Nombre: ");
                string ape = Validador::leerTextoValido("  Apellido: ");
                lu.crear(new Usuario(Validador::aMayusculas(nom),
                                     Validador::aMayusculas(ape), ced));
                cout << "  [OK] Usuario registrado.\n";
                GestorArchivos::guardarTodo(lu, lv, lr);
            }
            cout << "\n  Presione ENTER para continuar..."; cin.get();

        } else if (op == 2) {
            lu.reportar();
            cout << "\n  Presione ENTER para continuar..."; cin.get();

        } else if (op == 3) {
            cout << "\n--- MODIFICAR USUARIO ---\n";
            cout << "  Cedula a modificar: "; cin >> ced; cin.ignore(10000,'\n');
            if (!lu.buscar(ced)) { cout << "  [!] No encontrado.\n"; }
            else {
                string nom = Validador::leerTextoValido("  Nuevo Nombre: ");
                string ape = Validador::leerTextoValido("  Nuevo Apellido: ");
                lu.actualizar(ced, Validador::aMayusculas(nom), Validador::aMayusculas(ape));
                cout << "  [OK] Modificado.\n";
                GestorArchivos::guardarTodo(lu, lv, lr);
            }
            cout << "\n  Presione ENTER para continuar..."; cin.get();

        } else if (op == 4) {
            cout << "\n--- ELIMINAR USUARIO ---\n";
            cout << "  Cedula a eliminar: "; cin >> ced; cin.ignore(10000,'\n');
            lr.eliminarCascadaUsuario(ced);
            if (lu.eliminar(ced)) {
                cout << "  [OK] Usuario eliminado.\n";
                GestorArchivos::guardarTodo(lu, lv, lr);
            } else cout << "  [!] No encontrado.\n";
            cout << "\n  Presione ENTER para continuar..."; cin.get();

        } else if (op == 5) {
            // ── ORDENAMIENTO POR INTERCAMBIO CON ANIMACION ──
            cout << "\n  Iniciando ordenamiento por intercambio...\n";
            cout << "  Presione ENTER para ver la animacion..."; cin.get();
            lu.ordenamientoIntercambio();
            GestorArchivos::guardarTodo(lu, lv, lr);
            cout << "\n  [OK] Lista guardada ordenada.\n";
            cout << "\n  Presione ENTER para continuar..."; cin.get();

        } else if (op == 6) {
            // ── BUSQUEDA CON TRY/CATCH ──
            cout << "\n--- BUSCAR USUARIO (try/catch) ---\n";
            cout << "  Cedula: "; cin >> ced; cin.ignore(10000,'\n');
            Usuario* u = lu.buscarConExcepcion(ced);
            if (u) {
                cout << "\n  [ENCONTRADO]\n";
                cout << "  CI       : " << u->getCedula()   << "\n";
                cout << "  Nombre   : " << u->getNombre()   << "\n";
                cout << "  Apellido : " << u->getApellido() << "\n";
            }
            cout << "\n  Presione ENTER para continuar..."; cin.get();
        }
    } while (op != 7);
}

// ============================================================
//  MENU VEHICULOS
// ============================================================
void menuVehiculos(ListaVehiculos& lv, ListaDoble& lr, ListaUsuarios& lu) {
    vector<string> ops = {
        "Registrar Vehiculo",
        "Listar Vehiculos",
        "Modificar Placa",
        "Eliminar Vehiculo",
        "Volver al Menu Principal"
    };
    string placa, nueva;
    int op;
    do {
        op = menuMouse("GESTION DE VEHICULOS", ops);
        cls();

        if (op == 1) {
            cout << "\n--- REGISTRAR VEHICULO ---\n";
            do {
                cout << "  Placa (Ej: ABC-1234): "; cin >> placa; cin.ignore(10000,'\n');
                if (!Validador::validarPlaca(placa)) cout << "  [!] Formato invalido.\n";
            } while (!Validador::validarPlaca(placa));
            string pe = Validador::aMayusculas(placa);
            if (lv.buscar(pe)) cout << "  [!] Ya registrado.\n";
            else { lv.crear(new Vehiculo(pe)); cout << "  [OK] " << pe << " registrado.\n"; GestorArchivos::guardarTodo(lu,lv,lr); }
            cout << "\n  Presione ENTER..."; cin.get();

        } else if (op == 2) {
            lv.reportar();
            cout << "\n  Presione ENTER..."; cin.get();

        } else if (op == 3) {
            cout << "\n--- MODIFICAR PLACA ---\n";
            cout << "  Placa actual: "; cin >> placa; cin.ignore(10000,'\n');
            string pe = Validador::aMayusculas(placa);
            if (!lv.buscar(pe)) { cout << "  [!] No encontrado.\n"; cout << "\n  Presione ENTER..."; cin.get(); continue; }
            do {
                cout << "  Nueva placa: "; cin >> nueva; cin.ignore(10000,'\n');
                if (!Validador::validarPlaca(nueva)) cout << "  [!] Formato invalido.\n";
            } while (!Validador::validarPlaca(nueva));
            string ne = Validador::aMayusculas(nueva);
            if (lv.buscar(ne)) cout << "  [!] Esa placa ya existe.\n";
            else { lv.actualizar(pe, ne); cout << "  [OK] Placa actualizada.\n"; GestorArchivos::guardarTodo(lu,lv,lr); }
            cout << "\n  Presione ENTER..."; cin.get();

        } else if (op == 4) {
            cout << "\n--- ELIMINAR VEHICULO ---\n";
            cout << "  Placa: "; cin >> placa; cin.ignore(10000,'\n');
            string pe = Validador::aMayusculas(placa);
            lr.eliminarCascadaVehiculo(pe);
            if (lv.eliminar(pe)) { cout << "  [OK] Eliminado.\n"; GestorArchivos::guardarTodo(lu,lv,lr); }
            else cout << "  [!] No encontrado.\n";
            cout << "\n  Presione ENTER..."; cin.get();
        }
    } while (op != 5);
}

// ============================================================
//  MENU TURNOS
// ============================================================
void menuReservas(ListaDoble& lr, ListaUsuarios& lu, ListaVehiculos& lv) {
    auto nombreDia = [](auto& s, int w)->string{
        if(w==0)return"Domingo"; if(w==1)return"Lunes"; if(w==2)return"Martes";
        if(w==3)return"Miercoles"; if(w==4)return"Jueves"; if(w==5)return"Viernes";
        return"Sabado";
    };
    vector<string> ops = {
        "Registrar Turno",
        "Listar Turnos",
        "Modificar Fecha de Turno",
        "Cancelar Turno",
        "Buscar Turno por Placa",
        "Volver al Menu Principal"
    };
    string ced, placa;
    int op;
    do {
        op = menuMouse("GESTION DE TURNOS", ops);
        cls();

        if (op == 1) {
            cout << "\n--- REGISTRAR TURNO ---\n";
            cout << "  CI del propietario: "; cin >> ced; cin.ignore(10000,'\n');
            Usuario* u = lu.buscar(ced);
            if (!u) { cout << "  [!] Propietario no registrado.\n"; cout << "\n  ENTER..."; cin.get(); continue; }
            cout << "  Placa del vehiculo: "; cin >> placa; cin.ignore(10000,'\n');
            string pe = Validador::aMayusculas(placa);
            Vehiculo* v = lv.buscar(pe);
            if (!v) { cout << "  [!] Vehiculo no registrado.\n"; cout << "\n  ENTER..."; cin.get(); continue; }
            if (lr.buscarPorPlaca(pe)) { cout << "  [!] Ya tiene un turno activo.\n"; cout << "\n  ENTER..."; cin.get(); continue; }
            int dia,mes,anio;
            if (!pedirFechaReserva(dia,mes,anio)) { cout << "\n  ENTER..."; cin.get(); continue; }
            tm fecha={0}; fecha.tm_mday=dia; fecha.tm_mon=mes-1; fecha.tm_year=anio-1900;
            string razon = GestorFechas::ajustarFechaLaborable(&fecha);
            if (!razon.empty()) cout << "\n  [AVISO] " << razon << "\n";
            cout << "\n  [INFO] Fecha: " << nombreDia(nombreDia,fecha.tm_wday)
                 << " " << fecha.tm_mday << "/" << (fecha.tm_mon+1) << "/" << (fecha.tm_year+1900) << "\n";
            if (tienePicoYPlaca(pe, fecha.tm_wday)) {
                cout << "  [!] PICO Y PLACA ese dia. No se puede registrar.\n";
                cout << "\n  ENTER..."; cin.get(); continue;
            }
            int hora = elegirHora(lr, fecha.tm_mday, fecha.tm_mon+1, fecha.tm_year+1900);
            if (hora < 0) { cout << "\n  ENTER..."; cin.get(); continue; }
            lr.agregarReserva(new Reserva(u, v, fecha, hora));
            cout << "  [OK] Turno registrado a las " << hora << ":00.\n";
            GestorArchivos::guardarTodo(lu,lv,lr);
            cout << "\n  ENTER..."; cin.get();

        } else if (op == 2) {
            lr.mostrarReservas();
            cout << "\n  ENTER..."; cin.get();

        } else if (op == 3) {
            cout << "\n--- MODIFICAR FECHA ---\n";
            cout << "  Placa: "; cin >> placa; cin.ignore(10000,'\n');
            string pe = Validador::aMayusculas(placa);
            Reserva* r = lr.buscarPorPlaca(pe);
            if (!r) { cout << "  [!] No encontrado.\n"; cout << "\n  ENTER..."; cin.get(); continue; }
            int dia,mes,anio;
            if (!pedirFechaReserva(dia,mes,anio)) { cout << "\n  ENTER..."; cin.get(); continue; }
            tm fecha={0}; fecha.tm_mday=dia; fecha.tm_mon=mes-1; fecha.tm_year=anio-1900;
            GestorFechas::ajustarFechaLaborable(&fecha);
            r->setFechaAsignada(fecha);
            cout << "  [OK] Fecha actualizada.\n";
            GestorArchivos::guardarTodo(lu,lv,lr);
            cout << "\n  ENTER..."; cin.get();

        } else if (op == 4) {
            cout << "\n--- CANCELAR TURNO ---\n";
            cout << "  Placa: "; cin >> placa; cin.ignore(10000,'\n');
            if (lr.eliminarReserva(Validador::aMayusculas(placa))) {
                cout << "  [OK] Turno cancelado.\n"; GestorArchivos::guardarTodo(lu,lv,lr);
            } else cout << "  [!] No encontrado.\n";
            cout << "\n  ENTER..."; cin.get();

        } else if (op == 5) {
            cout << "\n--- BUSCAR TURNO ---\n";
            cout << "  Placa: "; cin >> placa; cin.ignore(10000,'\n');
            string pe = Validador::aMayusculas(placa);
            Reserva* r = lr.buscarPorPlaca(pe);
            if (!r) { cout << "  [!] No encontrado para " << pe << ".\n"; }
            else {
                tm f = r->getFechaAsignada();
                char fs[20]; snprintf(fs,sizeof(fs),"%02d/%02d/%04d",f.tm_mday,f.tm_mon+1,f.tm_year+1900);
                cout << "\n  Placa      : " << pe
                     << "\n  Fecha      : " << fs
                     << "\n  Hora       : " << r->getHoraAsignada() << ":00"
                     << "\n  Propietario: " << r->getUsuario()->getNombre()
                     << " " << r->getUsuario()->getApellido() << "\n";
            }
            cout << "\n  ENTER..."; cin.get();
        }
    } while (op != 6);
}

// ============================================================
//  MENU CIFRADO
// ============================================================
void menuCifrado() {
    vector<string> ops = {
        "Cifrado Cesar",
        "Cifrado XOR Bit a Bit",
        "Volver"
    };
    int op;
    do {
        op = menuMouse("METODOS DE CIFRADO", ops);
        cls();

        if (op == 1) {
            cout << "\n--- CIFRADO CESAR ---\n";
            string placa;
            cout << "  Placa (Ej: ABC-1234): "; cin >> placa; cin.ignore(10000,'\n');
            if (!Validador::validarPlaca(placa)) { cout << "  [!] Placa invalida.\n"; }
            else {
                int d = Validador::leerEntero("  Desplazamiento (1-25): ", 1, 25);
                string pm = Validador::aMayusculas(placa);
                string pc = Validador::cifrarPlacaCesar(pm, d);
                cout << "  Original : " << pm << "\n";
                cout << "  Cifrada  : " << pc << "\n";
            }
            cout << "\n  ENTER..."; cin.get();

        } else if (op == 2) {
            cout << "\n--- CIFRADO XOR BIT A BIT ---\n";
            cout << "  Texto a cifrar: "; string txt; getline(cin, txt);
            if (txt.empty()) { cout << "  [!] Vacio.\n"; cout << "\n  ENTER..."; cin.get(); continue; }
            txt = Validador::aMayusculas(txt);
            int clave = Validador::leerEntero("  Clave XOR (1-255): ", 1, 255);
            Validador::mostrarProcesoXOR(txt, (unsigned char)clave);
            string cifrado    = Validador::cifrarXOR(txt, (unsigned char)clave);
            string descifrado = Validador::descifrarXOR(cifrado, (unsigned char)clave);
            cout << "\n  [VERIFICACION] Descifrado: " << descifrado;
            cout << "  (Coincide: " << (descifrado==txt?"SI":"NO") << ")\n";
            cout << "\n  ENTER..."; cin.get();
        }
    } while (op != 3);
}

// ============================================================
//  MAIN
// ============================================================
int main() {
    ListaUsuarios  masterUsuarios;
    ListaVehiculos masterVehiculos;
    ListaDoble     masterReservas;

    cls();
    setColor(0x0B);
    cout << "\n  ==========================================\n";
    cout << "   SISTEMA DE MATRICULACION VEHICULAR    \n";
    cout << "         ECUADOR - Turnos de Revision    \n";
    cout << "  ==========================================\n";
    resetColor();
    cout << "\n  Cargando datos...\n";
    GestorArchivos::cargarTodo(masterUsuarios, masterVehiculos, masterReservas);
    cout << "  Carga completada. Presione ENTER...\n";
    cin.get();

    vector<string> opsPrincipal = {
        "Gestionar Usuarios",
        "Gestionar Vehiculos",
        "Gestionar Turnos / Reservas",
        "Cifrado de Datos",
        "Salir"
    };

    int op;
    do {
        op = menuMouse("SISTEMA DE MATRICULACION VEHICULAR - ECUADOR", opsPrincipal);
        switch (op) {
            case 1: menuUsuarios(masterUsuarios, masterReservas, masterVehiculos); break;
            case 2: menuVehiculos(masterVehiculos, masterReservas, masterUsuarios); break;
            case 3: menuReservas(masterReservas, masterUsuarios, masterVehiculos);  break;
            case 4: menuCifrado(); break;
            case 5: cls(); cout << "\n  Hasta pronto.\n\n"; break;
        }
    } while (op != 5);

    return 0;
}