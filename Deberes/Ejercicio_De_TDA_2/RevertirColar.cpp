/***********************************************************************
 * Module:  RevertirCola.cpp
 * Author:  USUARIO
 * Modified: s bado, 2 de mayo de 2026 19:32:32
 * Purpose: Implementation of the class RevertirCola
 ***********************************************************************/
#include "RevertirCola.h"
#include <iostream>

using namespace std;

void revertirCola(queue<int>& q) {
    stack<int> s;

    // Pasar de Cola a Pila
    while (!q.empty()) {
        s.push(q.front());
        q.pop();
    }

    //invierte el orden
    while (!s.empty()) {
        q.push(s.top());
        s.pop();
    }
}

void imprimirCola(queue<int> q) {
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}