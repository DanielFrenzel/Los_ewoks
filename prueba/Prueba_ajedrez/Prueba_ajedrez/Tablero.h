#pragma once
#include <vector>

using namespace std;

class Tablero
{
private:
	std::vector<std::vector<int>> tablero;
public:
	Tablero() : tablero(8, vector<int>(8, 0)) {}
	void dibujarTablero();
	void Inicializar();
};

