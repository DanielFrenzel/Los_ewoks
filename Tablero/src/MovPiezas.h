#pragma once
#include "Peon.h"
#include "Rey.h"
#include "Torre.h"
#include "Caballo.h"
#include "Alfil.h"

class MovPiezas
{
private:
	int ficha;
	Peon peon;
	Rey rey;
	Torre torre;
	Caballo caballo;
	Alfil alfil;
public:
	bool compMov(Casilla** casillas, int fil1, int col1, int fil2, int col2);
};

