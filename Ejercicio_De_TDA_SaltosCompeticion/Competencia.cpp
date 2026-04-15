#include "Competencia.h"
#include <iostream>

using namespace std;

Competencia::Competencia() : mejorSaltoGlobal(0.0), nombreGanador("") {}

void Competencia::ejecutarTorneo() {
    pedirDatos();
    calcularResultados();
    mostrarResultados();
}

void Competencia::pedirDatos() {
    cout << "=== COMPETENCIA DE SALTO LARGO ===" << endl;
    for (int i = 0; i < TOTAL_ATLETAS; i++) {
        string tempNombre;
        float temp1, temp2, temp3;

        cout << "\n--- Ingrese datos del Atleta " << (i + 1) << " ---" << endl;
        cout << "Nombre: ";
        cin >> tempNombre;
        Sal[i].setNombre(tempNombre);
        
        cout << "Salto 1 (metros): ";
        cin >> temp1;
        Sal[i].setIntento1(temp1);

        cout << "Salto 2 (metros): ";
        cin >> temp2;
        Sal[i].setIntento2(temp2);

        cout << "Salto 3 (metros): ";
        cin >> temp3;
        Sal[i].setIntento3(temp3);
    }
}

void Competencia::calcularResultados() {
    for (int i = 0; i < TOTAL_ATLETAS; i++) {
        // Encontrar el mejor salto de este atleta
        float mejorIndividual = Sal[i].getIntento1();
        if (Sal[i].getIntento2() > mejorIndividual) mejorIndividual = Sal[i].getIntento2();
        if (Sal[i].getIntento3() > mejorIndividual) mejorIndividual = Sal[i].getIntento3();

        Sal[i].setMejorIntento(mejorIndividual);

        // Actualizar el récord global si es necesario
        if (Sal[i].getMejorIntento() > mejorSaltoGlobal) {
            mejorSaltoGlobal = Sal[i].getMejorIntento();
            nombreGanador = Sal[i].getNombre();
        }
    }
}

void Competencia::mostrarResultados() {
    cout << "\n======================================" << endl;
    cout << "          RESULTADOS FINALES          " << endl;
    cout << "======================================" << endl;
    cout << "El ATLETA GANADOR es: " << nombreGanador << endl;
    cout << "Con un salto de: " << mejorSaltoGlobal << " metros." << endl;
}