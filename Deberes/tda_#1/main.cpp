
// main.cpp
#include <iostream>
#include "RutaLogistica.h"

using namespace std;

int main() {
    RutaLogistica camionReparto;

    // Ingresamos varios paquetes. Algunos con terminación EXP, otros normales.
    // Fíjate que la lambda soporta tanto mayúsculas como minúsculas ("exp")
    camionReparto.agregarPaquete("UIO-4458-NOR", "Quito");
    camionReparto.agregarPaquete("GYE-9912-EXP", "Guayaquil"); 
    camionReparto.agregarPaquete("CUE-1123-STD", "Cuenca");
    camionReparto.agregarPaquete("MNT-7741-exp", "Manta");    

    // Ejecutamos la auditoría con la lambda de punteros
    camionReparto.auditarRutaExpress();

    return 0; // Al salir del main, el destructor limpia toda la RAM dinamicamente.
}
