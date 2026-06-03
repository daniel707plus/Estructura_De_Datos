#include "Validador.h"
#include <iostream>
#include <cctype>
#include <algorithm>

// Convierte a mayusculas usando aritmetica de punteros
std::string Validador::aMayusculas(std::string texto) {
    std::string resultado = texto;
    char* ptr = &resultado.front();
    while (*ptr != '\0') {
        *ptr = toupper((unsigned char)*ptr);
        ptr++;
    }
    return resultado;
}

// Elimina espacios y tabulaciones al inicio y al final
// Usa punteros: avanza desde el frente y retrocede desde el final
std::string Validador::trim(std::string texto) {
    if (texto.empty()) return texto;

    const char* inicio = texto.c_str();
    // Avanzar desde el frente mientras haya espacios/tabs
    while (*inicio == ' ' || *inicio == '\t') inicio++;

    // Si quedo vacio (todo eran espacios)
    if (*inicio == '\0') return "";

    // Apuntar al ultimo caracter real
    const char* fin = texto.c_str() + texto.size() - 1;
    while (fin > inicio && (*fin == ' ' || *fin == '\t')) fin--;

    // Construir resultado desde inicio hasta fin (inclusive)
    return std::string(inicio, fin - inicio + 1);
}

// Valida que el texto (ya con trim) tenga solo letras y espacios simples
// No permite: vacio, solo espacios, numeros, simbolos
bool Validador::validarTexto(std::string texto) {
    std::string t = trim(texto);
    if (t.empty()) return false;

    const char* ptr = t.c_str();
    while (*ptr != '\0') {
        if (!isalpha((unsigned char)*ptr) && *ptr != ' ') return false;
        ptr++;
    }
    return true;
}

// Pide un nombre o apellido con validacion completa y mensajes especificos
std::string Validador::leerTextoValido(std::string mensaje) {
    std::string valor;
    while (true) {
        std::cout << mensaje;
        std::getline(std::cin, valor);

        // Limpiar \r de Windows
        if (!valor.empty() && valor.back() == '\r') valor.pop_back();

        std::string t = trim(valor);

        if (t.empty()) {
            std::cout << "  [!] El campo no puede estar vacio ni contener solo espacios.\n";
            continue;
        }

        // Verificar caracter por caracter con punteros
        const char* ptr = t.c_str();
        bool soloLetras = true;
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

        return t; // Retorna ya con trim aplicado
    }
}

// Valida Cedula Ecuatoriana usando aritmetica de punteros
bool Validador::validarCedula(std::string cedula) {
    if (cedula.length() != 10) return false;

    const char* ptr = cedula.c_str();

    const char* temp = ptr;
    while (*temp != '\0') {
        if (!isdigit((unsigned char)*temp)) return false;
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

    int digitoCalculado = (suma % 10 == 0) ? 0 : 10 - (suma % 10);
    int digitoReal = *(ptr + 9) - '0';

    return digitoCalculado == digitoReal;
}

// Valida placa ecuatoriana usando aritmetica de punteros
bool Validador::validarPlaca(std::string placa) {
    std::string p = aMayusculas(placa);
    p.erase(std::remove(p.begin(), p.end(), '-'), p.end());

    if (p.length() < 6 || p.length() > 7) return false;

    const char* ptr = p.c_str();

    for (int i = 0; i < 3; i++) {
        if (!isalpha((unsigned char)*(ptr + i))) return false;
    }

    for (size_t i = 3; i < p.length(); i++) {
        if (!isdigit((unsigned char)*(ptr + i))) return false;
    }

    char letraProvincia = *ptr;
    std::string provinciasValidas = "ABCEGHIJKLMNPQRSTUVWXYUZ";
    const char* provPtr = provinciasValidas.c_str();
    bool encontrada = false;
    while (*provPtr != '\0') {
        if (*provPtr == letraProvincia) { encontrada = true; break; }
        provPtr++;
    }
    return encontrada;
}

// Lee un entero en rango, rechaza letras y valores fuera del rango
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
        std::cout << "  [!] Entrada invalida. Ingrese un numero entre "
                  << min << " y " << max << ".\n";
    }
}
