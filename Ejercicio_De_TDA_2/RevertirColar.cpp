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

    // Pasar de Pila a Cola (esto invierte el orden)
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