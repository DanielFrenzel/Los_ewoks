#pragma once
#include "Casilla.h"
#include"Piezas.h"

class Torre :public Piezas
{
public:
	Torre() = default;
	Torre(char col);
	inline State comer(char color1, char color2)
	{
		if (color1 == color2) return INVALIDO;
		else return NORMAL;
	}
	State comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2) override;
	std::vector<Casilla*> movimientosPosibles(const TABLERO& tablero, Casilla& origen) override;
	void dibujar(float x, float y) override;
	char getColor() override;
	bool getMemoria() override { return false; }
	Tipo_pieza getTipo() override;
};
