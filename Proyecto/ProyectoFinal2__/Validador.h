#pragma once
#include <string>

class Validador {
public:
    // Convierte cualquier texto a mayusculas usando aritmetica de punteros
    static std::string aMayusculas(std::string texto);

    // Elimina espacios al inicio y al final del texto (trim)
    // Usa aritmetica de punteros sin corchetes
    static std::string trim(std::string texto);

    // Valida que el texto (ya con trim aplicado) tenga solo letras y espacios
    // y que no quede vacio ni sea solo espacios
    static bool validarTexto(std::string texto);

    // Pide un nombre/apellido validado: trim + no vacio + solo letras y espacios
    // Muestra mensaje de error especifico segun el fallo
    static std::string leerTextoValido(std::string mensaje);

    // Valida Cedula Ecuatoriana (Modulo 10, Personas Naturales)
    static bool validarCedula(std::string cedula);

    // Valida Placas Ecuatorianas (Ej: ABC-1234, verificando provincia)
    static bool validarPlaca(std::string placa);

    // Bucle indestructible para pedir numeros en consola
    static int leerEntero(std::string mensaje, int min, int max);
};
