#pragma once
#include <ctime>
#include <string>

class GestorFechas {
public:
    // Ajusta la fecha al siguiente dia laborable.
    // Retorna string vacio si ya era laborable, o un mensaje explicando
    // por que fue ajustada (fin de semana o feriado).
    static std::string ajustarFechaLaborable(std::tm* fecha);

    // Valida que la fecha no sea pasada y no supere 1 anio desde hoy.
    // Retorna "" si es valida, o un mensaje de error si no lo es.
    static std::string validarRangoFecha(int dia, int mes, int anio);
};
