#include "GestorFechas.h"

void GestorFechas::ajustarFechaLaborable(std::tm* fecha) {
    
    // 1. LAMBDAS DE UTILIDAD (Nuestro mktime manual)
    auto esBisiesto = [](int anio) -> bool {
        return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
    };

    auto diasDelMes = [&esBisiesto](int mes, int anio) -> int {
        if (mes == 2) return esBisiesto(anio) ? 29 : 28;
        if (mes == 4 || mes == 6 || mes == 9 || mes == 11) return 30;
        return 31; 
    };

    auto calcularDiaSemana = [](int dia, int mes, int anio) -> int {
        if (mes == 1 || mes == 2) { mes += 12; anio -= 1; }
        int K = anio % 100; int J = anio / 100;
        int h = (dia + (13 * (mes + 1)) / 5 + K + (K / 4) + (J / 4) + 5 * J) % 7;
        return (h + 6) % 7; // Dom=0, Lun=1...
    };

    auto miMktimeManual = [&diasDelMes, &calcularDiaSemana](std::tm* f) {
        int a = f->tm_year + 1900;
        int m = f->tm_mon + 1;
        int d = f->tm_mday;

        while (d <= 0) {
            m--; 
            if (m <= 0) { m = 12; a--; }
            d += diasDelMes(m, a);
        }
        while (d > diasDelMes(m, a)) {
            d -= diasDelMes(m, a);
            m++;
            if (m > 12) { m = 1; a++; }
        }

        f->tm_year = a - 1900; f->tm_mon = m - 1; f->tm_mday = d;
        f->tm_wday = calcularDiaSemana(d, m, a);
    };

    // 2. LAMBDAS DE FERIADOS
    auto esFeriadoObservado = [&miMktimeManual](std::tm* f) -> bool {
        int dEval = f->tm_mday;
        int mEval = f->tm_mon + 1;
        int aEval = f->tm_year + 1900;

        // Sub-Lambda: Toma un feriado fijo y aplica la LEY DE ECUADOR para saber que dia se descansa
        auto calcularDiaGoce = [&miMktimeManual, aEval](int d, int m) -> std::tm {
            std::tm feriado = {0}; 
            feriado.tm_mday = d; 
            feriado.tm_mon = m - 1; 
            feriado.tm_year = aEval - 1900;
            miMktimeManual(&feriado);
            
            // Ley de traslados sin usar un solo arreglo
            if (feriado.tm_wday == 6) feriado.tm_mday -= 1;      // Cae Sabado -> Se descansa Viernes
            else if (feriado.tm_wday == 0) feriado.tm_mday += 1; // Cae Domingo -> Se descansa Lunes
            else if (feriado.tm_wday == 2) feriado.tm_mday -= 1; // Cae Martes -> Se descansa Lunes
            else if (feriado.tm_wday == 3) feriado.tm_mday += 2; // Cae Miercoles -> Se descansa Viernes
            else if (feriado.tm_wday == 4) feriado.tm_mday += 1; // Cae Jueves -> Se descansa Viernes
            
            miMktimeManual(&feriado); // Re-normalizamos por si el traslado cambio de mes
            return feriado;
        };

        // Comprobamos si la fecha que el programa evalua choca con el DIA DE GOCE de los feriados fijos
        auto chocaConFijo = [&](int d, int m) -> bool {
            std::tm goce = calcularDiaGoce(d, m);
            return (goce.tm_mday == dEval && (goce.tm_mon + 1) == mEval);
        };

        // Comprobamos todos los feriados fijos de Ecuador
        if (chocaConFijo(1, 1) || chocaConFijo(1, 5) || chocaConFijo(24, 5) || 
            chocaConFijo(10, 8) || chocaConFijo(9, 10) || chocaConFijo(2, 11) || 
            chocaConFijo(3, 11) || chocaConFijo(25, 12)) {
            return true;
        }

        // Feriados Moviles (Algoritmo de Gauss para Carnaval y Viernes Santo)
        int A = aEval % 19; int B = aEval % 4; int C = aEval % 7; int K = aEval / 100;
        int P = (13 + 8 * K) / 25; int Q = K / 4;
        int M = (15 - P + K - Q) % 30; int N = (4 + K - Q) % 7;
        int D = (19 * A + M) % 30; int E = (2 * B + 4 * C + 6 * D + N) % 7;
        int mesPascua = 3; int diaPascua = 22 + D + E;
        if (diaPascua > 31) { mesPascua = 4; diaPascua = D + E - 9; }
        if (mesPascua == 4 && diaPascua == 26) diaPascua = 19;
        if (mesPascua == 4 && diaPascua == 25 && D == 28 && E == 6 && ((11 * M + 11) % 30 < 19)) diaPascua = 18;

        std::tm pascua = {0}; pascua.tm_year = aEval - 1900; pascua.tm_mon = mesPascua - 1; pascua.tm_mday = diaPascua;
        miMktimeManual(&pascua);

        std::tm lunCarnaval = pascua; lunCarnaval.tm_mday -= 48; miMktimeManual(&lunCarnaval);
        std::tm marCarnaval = pascua; marCarnaval.tm_mday -= 47; miMktimeManual(&marCarnaval);
        std::tm vieSanto = pascua; vieSanto.tm_mday -= 2; miMktimeManual(&vieSanto);

        if ((dEval == lunCarnaval.tm_mday && mEval == lunCarnaval.tm_mon + 1) ||
            (dEval == marCarnaval.tm_mday && mEval == marCarnaval.tm_mon + 1) ||
            (dEval == vieSanto.tm_mday && mEval == vieSanto.tm_mon + 1)) {
            return true;
        }

        return false;
    };

    // 3. PROCESAMIENTO PRINCIPAL LIMPIO Y BLINDADO
    miMktimeManual(fecha); // Normalizamos por si metieron dias raros como 32 de Enero

    bool ajustado = true;
    while (ajustado) {
        ajustado = false;
        
        // Regla 1: Fin de semana empuja al Lunes
        if (fecha->tm_wday == 0) { // Domingo -> Lunes
            fecha->tm_mday += 1;
            miMktimeManual(fecha);
            ajustado = true; 
        } else if (fecha->tm_wday == 6) { // Sabado -> Lunes
            fecha->tm_mday += 2;
            miMktimeManual(fecha);
            ajustado = true;
        }

        // Regla 2: Si es un DIA DE GOCE (feriado trasladado), se empuja 1 dia
        if (esFeriadoObservado(fecha)) {
            fecha->tm_mday += 1; 
            miMktimeManual(fecha);
            ajustado = true; // Se reinicia el ciclo porque el nuevo dia podria ser fin de semana
        }
    }
}