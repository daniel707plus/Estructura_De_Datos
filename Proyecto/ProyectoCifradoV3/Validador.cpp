#include "Validador.h"
#include <iostream>
#include <cctype>
#include <algorithm>
#include <windows.h>

std::string Validador::aMayusculas(std::string texto) {
    std::string resultado = texto;

    char* ptr = &resultado.front(); 
    

    while (*ptr != '\0') {
        *ptr = toupper(*ptr);
        ptr++; 
    }
    return resultado;
}


std::string Validador::trim(std::string texto) {
    if (texto.empty()) return texto;
    const char* inicio = texto.c_str();
    while (*inicio == ' ' || *inicio == '\t') inicio++;
    if (*inicio == '\0') return "";
    const char* fin = texto.c_str() + texto.size() - 1;
    while (fin > inicio && (*fin == ' ' || *fin == '\t')) fin--;
    return std::string(inicio, fin - inicio + 1);
}


std::string Validador::leerTextoValido(std::string mensaje) {
    std::string valor;
    while (true) {
        std::cout << mensaje;
        std::getline(std::cin, valor);
        if (!valor.empty() && valor.back() == '\r') valor.pop_back();
        std::string t = trim(valor);
        if (t.empty()) {
            std::cout << "  [!] El campo no puede estar vacio.\n";
            continue;
        }
        bool soloLetras = true;
        const char* ptr = t.c_str();
        while (*ptr != '\0') {
            if (!isalpha((unsigned char)*ptr) && *ptr != ' ') {
                soloLetras = false;
                break;
            }
            ptr++;
        }
        if (!soloLetras) {
            std::cout << "  [!] Solo se permiten letras y espacios. Sin numeros ni simbolos.\n";
            continue;
        }
        return t;
    }
}


bool Validador::validarTexto(std::string texto) {
    if (texto.empty()) return false;
    
    const char* ptr = texto.c_str(); 
    
    while (*ptr != '\0') {
        if (!isalpha(*ptr) && *ptr != ' ') return false;
        ptr++;
    }
    return true;
}

bool Validador::validarCedula(std::string cedula) {
    if (cedula.length() != 10) return false;
    
    const char* ptr = cedula.c_str();


    const char* temp = ptr;
    while (*temp != '\0') {
        if (!isdigit(*temp)) return false;
        temp++;
    }


    int provincia = (*ptr - '0') * 10 + (*(ptr + 1) - '0');
    if (provincia < 1 || (provincia > 24 && provincia != 30)) return false;


    int tercerDigito = *(ptr + 2) - '0';
    if (tercerDigito >= 6) return false;


    int suma = 0;
    for (int i = 0; i < 9; i++) {

        int valor = *(ptr + i) - '0'; 
        if (i % 2 == 0) { 
            valor *= 2;
            if (valor > 9) valor -= 9;
        }
        suma += valor;
    }

    int digitoVerificadorCalculado = (suma % 10 == 0) ? 0 : 10 - (suma % 10);

    int digitoVerificadorReal = *(ptr + 9) - '0';

    return digitoVerificadorCalculado == digitoVerificadorReal;
}

bool Validador::validarPlaca(std::string placa) {
    std::string p = aMayusculas(placa);
    p.erase(std::remove(p.begin(), p.end(), '-'), p.end());

    if (p.length() < 6 || p.length() > 7) return false;

    const char* ptr = p.c_str();


    for (int i = 0; i < 3; i++) {
        if (!isalpha(*(ptr + i))) return false;
    }


    for (size_t i = 3; i < p.length(); i++) {
        if (!isdigit(*(ptr + i))) return false;
    }


    char letraProvincia = *ptr;
    std::string provinciasValidas = "ABCEGHIJKLMNPQRSTUVWXYUZ";
    

    const char* provPtr = provinciasValidas.c_str();
    bool provinciaEncontrada = false;
    
    while (*provPtr != '\0') {
        if (*provPtr == letraProvincia) {
            provinciaEncontrada = true;
            break;
        }
        provPtr++;
    }
    
    if (!provinciaEncontrada) return false;

    return true;
}

int Validador::leerEntero(std::string mensaje, int min, int max) {
    int valor;
    while (true) {
        std::cout << mensaje;
        if (std::cin >> valor && valor >= min && valor <= max) {
            std::cin.ignore(10000, '\n'); 
            return valor;
        }
        std::cin.clear(); 
        std::cin.ignore(10000, '\n'); 
        std::cout << "Error: Entrada invalida. Ingrese un numero entre " << min << " y " << max << ".\n";
    }
}


std::string Validador::cifrarPlacaCesar(std::string placa, int desplazamiento) {

    std::string resultado = "";

  
    auto cifrar = [&](auto& self, int i) -> void {

  
        if (i == (int)placa.size()) return;

        char c = placa[i];

        if (c >= 'A' && c <= 'Z') {
 
            resultado += (char)('A' + (c - 'A' + desplazamiento) % 26);

        } else if (c >= '0' && c <= '9') {

            resultado += (char)('0' + (c - '0' + desplazamiento) % 10);

        } else {
 
            resultado += c;
        }


        self(self, i + 1);
    };

    cifrar(cifrar, 0);
    return resultado;
}

int Validador::leerOpcionPorClic(int lineaInicioY, int lineaFinY) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    
    // 1. GUARDAR EL MODO ORIGINAL
    // Si no hacemos esto, cin y getline() dejan de funcionar para siempre en todo el programa.
    DWORD modoOriginal;
    GetConsoleMode(hStdin, &modoOriginal);

    // 2. LIMPIAR EL BUFFER
    // Evita que clics viejos o movimientos de ratón generen opciones fantasma.
    FlushConsoleInputBuffer(hStdin);

    // 3. ACTIVAR MODO RATÓN Y APAGAR "QUICK EDIT" (que pausa la consola al hacer clic)
    DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
    SetConsoleMode(hStdin, fdwMode);

    INPUT_RECORD irInBuf[128];
    DWORD cNumRead;

    while (true) {
        // El programa se "pausa" aquí nativamente hasta detectar una acción
        ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead);
        
        for (DWORD i = 0; i < cNumRead; i++) {
            if (irInBuf[i].EventType == MOUSE_EVENT) {
                MOUSE_EVENT_RECORD mer = irInBuf[i].Event.MouseEvent;
                
                // Filtrar solo CLICKS ESTÁTICOS (ignorar que el usuario simplemente mueva el ratón)
                if (mer.dwEventFlags == 0 || mer.dwEventFlags == DOUBLE_CLICK) {
                    
                    // Si es el clic izquierdo
                    if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                        int clickY = mer.dwMousePosition.Y; // Fila donde dio clic
                        
                        // Si atinó en las líneas de las opciones
                        if (clickY >= lineaInicioY && clickY <= lineaFinY) {
                            
                            // 4. RESTAURAR EL MODO ORIGINAL ANTES DE SALIR
                            // Esto revive a std::cin para los menús de registro
                            SetConsoleMode(hStdin, modoOriginal);
                            
                            return clickY - lineaInicioY + 1; 
                        } else {
                            // Si hace clic fuera del menú, hace un pequeño sonido (Beep)
                            // Así el usuario sabe que el clic se detectó pero fue inválido, en lugar de creer que se colgó.
                            Beep(500, 150); 
                        }
                    }
                }
            }
        }
    }
}