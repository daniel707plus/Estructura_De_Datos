#include <iostream>
#include "Fecha.h"
using namespace std;

Fecha::Fecha() {
    dia  = 1;
    mes  = 1;
    anio = 2026;
}

Fecha::Fecha(int d, int m, int a) {
    dia  = d;
    mes  = m;
    anio = a;
}

int Fecha::getDia()  { return dia;  }
int Fecha::getMes()  { return mes;  }
int Fecha::getAnio() { return anio; }

string Fecha::toString() {
    // Agrega un cero adelante si el numero tiene un solo digito
    string sd = (dia  < 10) ? "0" + to_string(dia)  : to_string(dia);
    string sm = (mes  < 10) ? "0" + to_string(mes)  : to_string(mes);
    string sa = to_string(anio);
    return sd + "/" + sm + "/" + sa;
}

bool Fecha::esValida() {
    if (mes < 1 || mes > 12) return false;
    if (dia < 1)             return false;
    if (anio < 2000)         return false;

    // Cuantos dias tiene cada mes
    int diasDelMes[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Si el año es bisiesto, febrero tiene 29 dias
    bool bisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
    if (bisiesto) diasDelMes[2] = 29;

    if (dia > diasDelMes[mes]) return false;

    return true;
}

// Algoritmo de Zeller simplificado
// Devuelve: 0=domingo, 1=lunes, 2=martes, 3=mier, 4=juev, 5=vier, 6=sabado
int diaDeLaSemana(int d, int m, int a) {
    if (m < 3) {
        m += 12;
        a -= 1;
    }
    int k = a % 100;
    int j = a / 100;
    int h = (d + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;
    // Convertir del resultado de Zeller (2=lunes...0=sabado) al clasico
    int diaSemana = ((h + 5) % 7) + 1; // 1=lunes ... 7=domingo
    // Reajustar para que 0=domingo, 1=lunes...6=sabado
    return diaSemana % 7; // 0=domingo,1=lunes,...,6=sabado
}

bool Fecha::esDiaLaborable() {
    int ds = diaDeLaSemana(dia, mes, anio);
    // 0 = domingo, 6 = sabado
    return (ds != 0 && ds != 6);
}

// Avanza un dia en el calendario (maneja cambio de mes y año)
void avanzarUnDia(int &d, int &m, int &a) {
    int diasDelMes[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool bisiesto = (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
    if (bisiesto) diasDelMes[2] = 29;

    d++;
    if (d > diasDelMes[m]) {
        d = 1;
        m++;
        if (m > 12) {
            m = 1;
            a++;
        }
    }
}

void Fecha::ajustarADiaLaborable() {
    // Si cae en fin de semana avanza hasta el lunes
    while (!esDiaLaborable()) {
        avanzarUnDia(dia, mes, anio);
    }
}

Fecha Fecha::sumarDiasLaborables(int n) {
    int d = dia, m = mes, a = anio;
    int contados = 0;

    while (contados < n) {
        avanzarUnDia(d, m, a);
        int ds = diaDeLaSemana(d, m, a);
        if (ds != 0 && ds != 6) {
            contados++;
        }
    }
    return Fecha(d, m, a);
}

bool Fecha::esIgual(Fecha otra) {
    return (dia == otra.dia && mes == otra.mes && anio == otra.anio);
}

// Lee una fecha del teclado con formato DD/MM/AAAA
// Si el usuario escribe algo incorrecto se lo vuelve a pedir
Fecha leerFecha() {
    while (true) {
        string entrada;
        cout << "Ingrese la fecha (DD/MM/AAAA): ";
        cin >> entrada;

        // Necesitamos al menos 10 caracteres: "DD/MM/AAAA"
        if (entrada.size() != 10) {
            cout << "Formato incorrecto. Use DD/MM/AAAA\n";
            continue;
        }

        if (entrada[2] != '/' || entrada[5] != '/') {
            cout << "Formato incorrecto. Use DD/MM/AAAA\n";
            continue;
        }

        // Separar los numeros
        string sDia  = entrada.substr(0, 2);
        string sMes  = entrada.substr(3, 2);
        string sAnio = entrada.substr(6, 4);

        // Verificar que sean numeros
        bool soloNumeros = true;
        for (int i = 0; i < 2; i++) {
            if (sDia[i]  < '0' || sDia[i]  > '9') soloNumeros = false;
            if (sMes[i]  < '0' || sMes[i]  > '9') soloNumeros = false;
        }
        for (int i = 0; i < 4; i++) {
            if (sAnio[i] < '0' || sAnio[i] > '9') soloNumeros = false;
        }

        if (!soloNumeros) {
            cout << "Solo se permiten numeros en la fecha.\n";
            continue;
        }

        int d = stoi(sDia);
        int m = stoi(sMes);
        int a = stoi(sAnio);

        Fecha f(d, m, a);
        if (!f.esValida()) {
            cout << "La fecha no es valida. Intente de nuevo.\n";
            continue;
        }

        return f;
    }
}
