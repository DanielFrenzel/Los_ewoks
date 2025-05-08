#pragma once
#include "Casilla.h"
#include"Piezas.h"
#include"Alfil.h"
#include"Torre.h"
#include<cmath>

class Reina :public Piezas
{
public:
	Reina(char col);
	bool comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2) override;
	void dibujar(float x, float y) override;
	char getColor() override;
};

