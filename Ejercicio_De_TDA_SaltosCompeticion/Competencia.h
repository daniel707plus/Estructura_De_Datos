#ifndef COMPETENCIA_H
#define COMPETENCIA_H

#include "ICompetencia.h" 
#include "Salto.h"        
#include <string>

class Competencia : public ICompetencia {
private:
    static const int TOTAL_ATLETAS = 5;
    Salto Sal[TOTAL_ATLETAS];
    float mejorSaltoGlobal;
    std::string nombreGanador;

    void pedirDatos();
    void calcularResultados();
    void mostrarResultados();

public:
    Competencia();
    void ejecutarTorneo() override; 
};

#endif