#include "VerificarCedula.h"
#include <iostream>

bool VerificarCedula::validarCedula(const std::string &cedula) {

    if (cedula.length() != 10) return false;

    int provincia = std::stoi(cedula.substr(0, 2));
    if (provincia < 1 || provincia > 24) return false;


    int suma = 0;
    for (int i = 0; i < 9; i++) {
        int digito = cedula[i] - '0';
        if (i % 2 == 0) { 
            digito *= 2;
            if (digito > 9) digito -= 9;
        }
        suma += digito;
    }

    int digitoVerificador = cedula[9] - '0';
    int decenaSuperior = ((suma + 9) / 10) * 10;
    int resultado = decenaSuperior - suma;

    return (resultado == digitoVerificador);
}