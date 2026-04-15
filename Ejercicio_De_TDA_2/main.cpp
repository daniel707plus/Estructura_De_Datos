#include <iostream>
#include <queue>
#include "RevertirCola.h"

using namespace std;

int main() {
    queue<int> miCola;

    for (int i = 1; i <= 5; ++i) {
        miCola.push(i * 10);
    }

    cout << "--- Estado Inicial ---" << endl;
    cout << "Cola: ";
    imprimirCola(miCola);

    revertirCola(miCola);

    cout << "\n--- Estado Final ---" << endl;
    cout << "Cola revertida: ";
    imprimirCola(miCola);

    return 0;
}