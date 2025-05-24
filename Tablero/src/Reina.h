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
	State comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2) override;
	std::vector<Casilla*> movimientosPosibles(const TABLERO& tablero, Casilla& origen) override;
	void dibujar(float x, float y) override;
	char getColor() override;
	bool getMemoria() override { return false; }
	Tipo_pieza getTipo() override;
};



