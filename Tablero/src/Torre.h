#pragma once
#include "Casilla.h"

class Torre
{
public:
	bool ComprobarMov(Casilla casillas[8][8], int fil1, int col1, int fil2, int col2);
};
