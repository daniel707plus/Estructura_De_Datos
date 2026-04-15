#include "Proceso.h"
#include <iostream>
using namespace std;


template <typename T>
Quebrado<T> Proceso<T>::sumar(Quebrado<T> q1, Quebrado<T> q2) {
    
    T num = q1.getNumerador() * q2.getDenominador() + q2.getNumerador() * q1.getDenominador();
    T den = q1.getDenominador() * q2.getDenominador();
    Quebrado<T> resultado;
    resultado.setNumerador(num);
    resultado.setDenominador(den);
    return resultado;
}

template <typename T>
void Proceso<T>::mostrar(Quebrado<T> q) {
    cout << q.getNumerador() << "/" << q.getDenominador() <<endl;
}
