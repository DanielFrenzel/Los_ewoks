#pragma once
#include "Piezas.h"
#include"Casilla.h"
#include<cmath>

class Alfil :public Piezas
{
public:
	Alfil() = default;
	Alfil(char col);
	bool comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2) override;
	void dibujar(float x, float y) override;
	char getColor() override;
};

