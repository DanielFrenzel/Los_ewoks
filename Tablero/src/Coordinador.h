#pragma once
#include "Tablero.h"
#include"Casilla.h"
#include "Peon.h"
#include "Rey.h"
#include "Torre.h"
#include "Caballo.h"
#include "Alfil.h"

class Coordinador
{
private:
	Tablero* tablero = nullptr;
	int ficha;
	Peon peon;
	Rey rey;
	Torre torre;
	Caballo caballo;
	Alfil alfil;
	bool turno = 0;

public:
	void setTablero(Tablero* t);
	void MovRaton(int x, int y);
	void movimiento(int fil1, int col1, int fil2, int col2);
	bool compMov(int fil1, int col1, int fil2, int col2);
};

