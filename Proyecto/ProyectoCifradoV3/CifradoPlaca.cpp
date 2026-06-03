#include "CifradoPlaca.h"
#include <fstream>
#include <iostream>
#include <cctype>

void CifradoPlaca::cifrarDesdeArchivo(const char* rutaArchivo) {

    //REDUCCION DIGITAL 
    auto reducir = [](auto& self, int n) -> int {
        if (n < 10) return n;
        int suma = 0;
        int* ptr = &n;
        while (*ptr > 0) {
            suma += *ptr % 10;
            *ptr /= 10;
        }
        return self(self, suma);
    };

    //  CIFRADO DE UN CARACTER LETRA 
    auto cifrarLetra = [&reducir](char c) -> int {
        char* ptr = &c;
        if (*ptr >= 'A' && *ptr <= 'Z') *ptr = *ptr + 32;

        int ascii = (unsigned char)(*ptr);

        return reducir(reducir, ascii);
    };

    // ACUMULACION CON REDUCCION 
    auto acumular = [&reducir](int acum, int nuevo) -> int {
        return reducir(reducir, acum + nuevo);
    };

    // CIFRADO DE LA PARTE LETRAS DE UNA PLACA
    auto cifrarParteletras = [&cifrarLetra, &acumular](const char* placa) -> int {
        const char* ptr = placa;
        int acum = 0;

        const char* fin = ptr + 3;
        while (ptr != fin) {
            int valorLetra = cifrarLetra(*ptr);
            acum = (acum == 0) ? valorLetra : acumular(acum, valorLetra);
            ++ptr;
        }
        return acum;
    };

    // CIFRADO DE LA PARTE NUMEROS
    auto cifrarParteNumeros = [&acumular](const char* placa) -> int {
        // Avanzar puntero hasta despues del guion
        const char* ptr = placa;
        while (*ptr && *ptr != '-') ++ptr;
        if (*ptr == '-') ++ptr; // saltar el guion

        int acum = 0;
        while (*ptr && *ptr >= '0' && *ptr <= '9') {
            int digito = *ptr - '0';
            acum = acumular(acum, digito);
            ++ptr;
        }
        return acum;
    };


    auto construirResultado = [](int cifNumeros, int cifLetras) -> int {
        return cifLetras * 10 + cifNumeros;
    };

    // --- LECTURA DEL ARCHIVO Y PROCESAMIENTO ---
    std::ifstream arch(rutaArchivo);
    if (!arch.is_open()) {
        std::cout << "[!] No se pudo abrir: " << rutaArchivo << "\n";
        return;
    }

    std::cout << "\n========== CIFRADO DE PLACAS ==========\n";

    std::string linea;
    while (std::getline(arch, linea)) {

        while (!linea.empty() && (linea.back() == '\r' || linea.back() == ' '))
            linea.pop_back();
        if (linea.empty()) continue;

        const char* placa = linea.c_str();

        int cifLetras  = cifrarParteletras(placa);
        int cifNumeros = cifrarParteNumeros(placa);
        int resultado  = construirResultado(cifNumeros, cifLetras);

        std::cout << "Placa   : " << placa        << "\n";
        std::cout << "Letras  : " << cifLetras    << "\n";
        std::cout << "Numeros : " << cifNumeros   << "\n";
        std::cout << "Cifrado : " << resultado    << "\n";
        std::cout << "---------------------------------------\n";
    }

    arch.close();
}
