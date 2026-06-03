#ifndef FECHA_H
#define FECHA_H

#include <string>
using namespace std;

// Esta clase guarda una fecha y tiene herramientas para trabajar con dias laborables
class Fecha {
private:
    int dia;
    int mes;
    int anio;

public:
    Fecha();
    Fecha(int d, int m, int a);

    int getDia();
    int getMes();
    int getAnio();

    // Convierte la fecha a texto "DD/MM/AAAA"
    string toString();

    // Revisa si la fecha es valida (que no sea mes 13, dia 32, etc.)
    bool esValida();

    // Dice si ese dia es sabado (6) o domingo (0)
    // Usamos el algoritmo de Zeller para saber el dia de la semana
    bool esDiaLaborable();

    // Avanza la fecha al siguiente dia laborable si cae en fin de semana
    void ajustarADiaLaborable();

    // Suma N dias laborables a la fecha
    Fecha sumarDiasLaborables(int n);

    // Compara si esta fecha es igual a otra
    bool esIgual(Fecha otra);
};

// Lee una fecha del teclado en formato DD/MM/AAAA
// Si el usuario escribe mal, le vuelve a pedir
Fecha leerFecha();

#endif
