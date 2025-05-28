#pragma once
#include "Casilla.h"
#include"Piezas.h"
#include<cmath>

class Caballo :public Piezas
{
public:
	Caballo() = default;
	Caballo(char col);
	State comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2, int peon_doble_avance_fila_anterior, int peon_doble_avance_clomuna_anterior) override;
	std::vector<Casilla*> movimientosPosibles(const TABLERO& tablero, Casilla& origen) override;
	void dibujar(float x, float y) override;
	char getColor() override;
	bool getMemoria() override { return false; }
	Tipo_pieza getTipo() override;
};

