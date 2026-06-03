#include "GestorFechas.h"

void GestorFechas::ajustarFechaLaborable(std::tm* fecha) {

    // ---- LAMBDAS DE UTILIDAD ----

    // Lambda: determina si un año es bisiesto
    auto esBisiesto = [](int anio) -> bool {
        return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
    };

    // Lambda: dias que tiene un mes especifico
    auto diasDelMes = [&esBisiesto](int mes, int anio) -> int {
        if (mes == 2) return esBisiesto(anio) ? 29 : 28;
        if (mes == 4 || mes == 6 || mes == 9 || mes == 11) return 30;
        return 31;
    };

    // Lambda: algoritmo de Zeller para obtener el dia de semana
    // Retorna: 0=Domingo, 1=Lunes, ... 6=Sabado
    auto calcularDiaSemana = [](int dia, int mes, int anio) -> int {
        if (mes == 1 || mes == 2) { mes += 12; anio -= 1; }
        int K = anio % 100;
        int J = anio / 100;
        int h = (dia + (13 * (mes + 1)) / 5 + K + (K / 4) + (J / 4) + 5 * J) % 7;
        return (h + 6) % 7;
    };

    // Lambda: normaliza una fecha (desbordamiento de dias/meses)
    auto miMktimeManual = [&diasDelMes, &calcularDiaSemana](std::tm* f) {
        int a = f->tm_year + 1900;
        int m = f->tm_mon  + 1;
        int d = f->tm_mday;
        while (d <= 0) { m--; if (m <= 0) { m = 12; a--; } d += diasDelMes(m, a); }
        while (d > diasDelMes(m, a)) { d -= diasDelMes(m, a); m++; if (m > 12) { m = 1; a++; } }
        f->tm_year = a - 1900;
        f->tm_mon  = m - 1;
        f->tm_mday = d;
        f->tm_wday = calcularDiaSemana(d, m, a);
    };

    // Lambda: verifica si una fecha es feriado en Ecuador
    // Usa el Algoritmo de Gauss para calcular Semana Santa
    auto esFeriado = [&miMktimeManual](std::tm* f) -> bool {
        int d = f->tm_mday;
        int m = f->tm_mon + 1;
        int a = f->tm_year + 1900;

        // Feriados fijos Ecuador
        if ((d==1  && m==1)  || (d==1  && m==5)  || (d==24 && m==5) ||
            (d==10 && m==8)  || (d==9  && m==10) || (d==2  && m==11)||
            (d==3  && m==11) || (d==25 && m==12)) {
            return true;
        }

        // Gauss: calcular fecha de Pascua
        int A = a % 19; int B = a % 4;  int C = a % 7;
        int K = a / 100; int P = (13 + 8*K)/25; int Q = K/4;
        int M = (15 - P + K - Q) % 30;
        int N = (4  + K - Q) % 7;
        int D = (19*A + M) % 30;
        int E = (2*B + 4*C + 6*D + N) % 7;
        int mesPascua = 3; int diaPascua = 22 + D + E;
        if (diaPascua > 31) { mesPascua = 4; diaPascua = D + E - 9; }
        if (mesPascua == 4 && diaPascua == 26) diaPascua = 19;
        if (mesPascua == 4 && diaPascua == 25 && D == 28 && E == 6 && ((11*M+11)%30 < 19)) diaPascua = 18;

        std::tm pascua = {0};
        pascua.tm_year = a - 1900; pascua.tm_mon = mesPascua - 1; pascua.tm_mday = diaPascua;
        miMktimeManual(&pascua);

        std::tm lunCarnaval = pascua; lunCarnaval.tm_mday -= 48; miMktimeManual(&lunCarnaval);
        std::tm marCarnaval = pascua; marCarnaval.tm_mday -= 47; miMktimeManual(&marCarnaval);
        std::tm vieSanto    = pascua; vieSanto.tm_mday    -= 2;  miMktimeManual(&vieSanto);

        if (d == lunCarnaval.tm_mday && m == lunCarnaval.tm_mon+1) return true;
        if (d == marCarnaval.tm_mday && m == marCarnaval.tm_mon+1) return true;
        if (d == vieSanto.tm_mday    && m == vieSanto.tm_mon+1)    return true;

        return false;
    };

    // ---- PROCESAMIENTO PRINCIPAL ----
    miMktimeManual(fecha); // normalizar primero

    bool ajustado = true;
    while (ajustado) {
        ajustado = false;

        // Si cae fin de semana -> empujar al lunes siguiente
        if (fecha->tm_wday == 0) {       // Domingo -> Lunes
            fecha->tm_mday += 1;
            miMktimeManual(fecha);
            ajustado = true;
        } else if (fecha->tm_wday == 6) { // Sabado -> Lunes
            fecha->tm_mday += 2;
            miMktimeManual(fecha);
            ajustado = true;
        }

        // Si es feriado -> aplicar Ley de Feriados de Ecuador
        if (esFeriado(fecha)) {
            if (fecha->tm_wday == 2) {                // Martes -> se traslada al Lunes
                fecha->tm_mday -= 1;
            } else if (fecha->tm_wday == 3 || fecha->tm_wday == 4) { // Mier/Jue -> al Viernes
                fecha->tm_mday += (6 - fecha->tm_wday) - 1;
            } else {
                fecha->tm_mday += 1;                  // Lunes/Viernes -> al siguiente dia
            }
            miMktimeManual(fecha);
            ajustado = true;
        }
    }
}
