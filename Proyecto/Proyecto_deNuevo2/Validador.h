#pragma once
#include <string>

class Validador {
public:
    // Convierte cualquier texto a mayúsculas para guardar los datos limpios
    static std::string aMayusculas(std::string texto);

    // Valida que el texto solo contenga letras y espacios (para nombres y apellidos)
    static bool validarTexto(std::string texto);

    // Valida Cédula Ecuatoriana (Módulo 10, Personas Naturales)
    static bool validarCedula(std::string cedula);

    // Valida Placas Ecuatorianas (Ej: ABC-1234 o ABC1234, verificando provincia)
    static bool validarPlaca(std::string placa);

    // Bucle indestructible para pedir números en consola (Menús, Días, Meses, etc.)
    static int leerEntero(std::string mensaje, int min, int max);
};