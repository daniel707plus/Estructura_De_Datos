#include "Competencia.h"

int main() {
    ICompetencia* torneo = new Competencia();
  
    torneo->ejecutarTorneo();
    
    delete torneo;
    
    return 0;
}