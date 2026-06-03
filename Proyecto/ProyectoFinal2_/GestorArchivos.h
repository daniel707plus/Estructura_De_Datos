#pragma once
#include "ListaUsuarios.h"
#include "ListaVehiculos.h"
#include "ListaDoble.h"

// ============================================================
//  GESTOR DE ARCHIVOS - Persistencia en .txt
//
//  Formato usuarios.txt  (una linea por usuario):
//    CEDULA|NOMBRE|APELLIDO
//
//  Formato vehiculos.txt (una linea por vehiculo):
//    PLACA
//
//  Formato reservas.txt  (una linea por reserva):
//    CEDULA_USUARIO|PLACA_VEHICULO|DIA|MES|ANIO|WDAY
//
//  Separador: '|'  (no puede aparecer en ningun campo)
// ============================================================

class GestorArchivos {
public:
    // Guarda los tres archivos. Retorna true si los tres tuvieron exito.
    static bool guardarTodo(const ListaUsuarios& lu,
                            const ListaVehiculos& lv,
                            const ListaDoble&     lr);

    // Carga los tres archivos en las listas (que deben estar vacias).
    // Retorna true si los tres archivos existian y se leyeron bien.
    static bool cargarTodo(ListaUsuarios& lu,
                           ListaVehiculos& lv,
                           ListaDoble&     lr);
};
