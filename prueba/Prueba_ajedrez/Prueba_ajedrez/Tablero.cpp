#include "Tablero.h"
#include <iostream>
#include <vector>

using namespace std;


void Tablero::dibujarTablero() {
    cout << "---------------------------------" << endl; // Línea superior
    for (int i = 0; i < 8; i++) {
        cout << "| "; // Borde izquierdo
        for (int j = 0; j < 8; j++) {
            cout << tablero[i][j] << " | "; // Valor con separación
        }
        cout << endl << "---------------------------------" << endl; // Línea horizontal
    }
}

void Tablero::Inicializar() {
    // Primeros 8 valores
    int valores1[] = { 1, 2, 3, 4, 5, 3, 2, 1 };
    for (int j = 0; j < 8; j++) {
        tablero[0][j] = valores1[j]; // Primera fila
    }

    // Siguientes 8 valores en 6
    for (int j = 0; j < 8; j++) {
        tablero[1][j] = 6; // Segunda fila
    }

    // Siguientes 4 filas ya están en 0 por la inicialización

    // Penúltimos 8 valores (negativo de la primera fila)
    for (int j = 0; j < 8; j++) {
        tablero[6][j] = -valores1[7 - j]; // Séptima fila (invertida)
    }

    // Últimos 8 valores en -6
    for (int j = 0; j < 8; j++) {
        tablero[7][j] = -6; // Octava fila
    }
}
