#pragma once
#include "Casilla.h"
#include"Piezas.h"
#include<cmath>

class Caballo :public Piezas
{
public:
	Caballo() = default;
	Caballo(char col);
	bool comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2) override;
	void dibujar(float x, float y) override;
	char getColor() override;
};

