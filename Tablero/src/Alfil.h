#pragma once
#include "Piezas.h"
#include"Casilla.h"
#include<cmath>

class Alfil :public Piezas
{
public:
	Alfil() = default;
	Alfil(char col);
	State comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2) override;
	std::vector<Casilla*> movimientosPosibles(const TABLERO& tablero, Casilla& origen) override;
	void dibujar(float x, float y) override;
	char getColor() override;
	bool getMemoria() override { return false; }
	Tipo_pieza getTipo() override;
};

