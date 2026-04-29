#ifndef MATRIZ_H
#define MATRIZ_H

class Matriz {
private:
    int filas;
    int columnas;
    int** m; // El doble puntero

    void liberarMemoria(); // Metodo privado de ayuda

public:
    Matriz(int f, int c);
    Matriz(const Matriz& otra); // Constructor de copia (importante nivel intermedio)
    ~Matriz();

    // Sobrecarga del igual (obligatorio cuando hay punteros dinámicos)
    Matriz& operator=(const Matriz& otra);

    // Getters y Setters
    int getFilas() const;
    int getColumnas() const;
    void setDato(int f, int c, int valor);
    int getDato(int f, int c) const;
};

#endif