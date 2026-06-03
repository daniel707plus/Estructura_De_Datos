#include "Validador.h"
#include <iostream>
#include <cctype>
#include <algorithm>

std::string Validador::aMayusculas(std::string texto) {
    std::string resultado = texto;
    // Extraemos un puntero al inicio del string
    char* ptr = &resultado.front(); 
    
    // Mientras no lleguemos al caracter nulo '\0' que indica el fin del string
    while (*ptr != '\0') {
        *ptr = toupper(*ptr);
        ptr++; // Avanzamos el puntero al siguiente byte/caracter
    }
    return resultado;
}

bool Validador::validarTexto(std::string texto) {
    if (texto.empty()) return false;
    
    const char* ptr = texto.c_str(); // Puntero de solo lectura
    
    while (*ptr != '\0') {
        if (!isalpha(*ptr) && *ptr != ' ') return false;
        ptr++;
    }
    return true;
}

bool Validador::validarCedula(std::string cedula) {
    if (cedula.length() != 10) return false;
    
    const char* ptr = cedula.c_str();

    // 1. Validar que todos sean digitos usando un puntero temporal
    const char* temp = ptr;
    while (*temp != '\0') {
        if (!isdigit(*temp)) return false;
        temp++;
    }

    // 2. Codigo de Provincia (Posiciones 0 y 1)
    // Desreferenciamos el puntero para obtener los caracteres y los convertimos a enteros
    int provincia = (*ptr - '0') * 10 + (*(ptr + 1) - '0');
    if (provincia < 1 || (provincia > 24 && provincia != 30)) return false;

    // 3. Tercer digito (Posicion 2)
    int tercerDigito = *(ptr + 2) - '0';
    if (tercerDigito >= 6) return false;

    // 4. Algoritmo Modulo 10
    int suma = 0;
    for (int i = 0; i < 9; i++) {
        // Aritmetica de punteros pura: *(ptr + i) en lugar de ptr[i]
        int valor = *(ptr + i) - '0'; 
        if (i % 2 == 0) { 
            valor *= 2;
            if (valor > 9) valor -= 9;
        }
        suma += valor;
    }

    int digitoVerificadorCalculado = (suma % 10 == 0) ? 0 : 10 - (suma % 10);
    // Posicion 9 de la cedula
    int digitoVerificadorReal = *(ptr + 9) - '0';

    return digitoVerificadorCalculado == digitoVerificadorReal;
}

bool Validador::validarPlaca(std::string placa) {
    std::string p = aMayusculas(placa);
    p.erase(std::remove(p.begin(), p.end(), '-'), p.end());

    if (p.length() < 6 || p.length() > 7) return false;

    const char* ptr = p.c_str();

    // Primeros 3 caracteres deben ser letras
    for (int i = 0; i < 3; i++) {
        if (!isalpha(*(ptr + i))) return false;
    }

    // Resto deben ser numeros
    for (size_t i = 3; i < p.length(); i++) {
        if (!isdigit(*(ptr + i))) return false;
    }

    // Validar primera letra (Posicion 0, o sea *ptr)
    char letraProvincia = *ptr;
    std::string provinciasValidas = "ABCEGHIJKLMNPQRSTUVWXYUZ";
    
    // Usamos punteros tambien para buscar en el string de provincias validas
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