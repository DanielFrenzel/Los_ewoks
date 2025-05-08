#pragma once
#include "Casilla.h"
#include"Piezas.h"

class Torre:public Piezas
{
public:
	Torre(char col);
	inline bool comer(char color1, char color2)
	{
		if (color1 == color2) return 0;
		else return 1;
	}
	bool comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2) override;
	void dibujar(float x, float y) override;
	char getColor() override;
};
