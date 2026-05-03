/***********************************************************************
 * Module:  Matriz.h
 * Author:  USUARIO
 * Modified: s�bado, 2 de mayo de 2026 19:32:32
 * Purpose: Declaration of the class Matriz
 ***********************************************************************/

#ifndef MATRIZ_H
#define MATRIZ_H

class Matriz {
private:
    int filas;
    int columnas;
    int** m; // El doble puntero

    void liberarMemoria(); 

public:
    Matriz(int f, int c);
    Matriz(const Matriz& otra); 
    ~Matriz();


    int getFilas() const;
    int getColumnas() const;
    void setDato(int f, int c, int valor);
    int getDato(int f, int c) const;
};

#endif