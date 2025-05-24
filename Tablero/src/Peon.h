#pragma once
#include"ETSIDI.h"
#include"Piezas.h"
#include "Casilla.h"
#include<cmath>

class Peon :public Piezas							//Heredamos de la clase Piezas
{
private:
	bool memoria;
	bool capturaPaso;
public:
	Peon() = default;
	Peon(char col);									//Constructor

	State comprobarMov(TABLERO& casillas,			//Funcion de comprobar movimiento de la clase Peon
		Casilla& cas1, Casilla& cas2) override;
	std::vector<Casilla*> movimientosPosibles(const TABLERO& tablero, Casilla& origen) override;
	void dibujar(float x, float y) override;		//Funcion de dibujar de la clase Peon
	char getColor() override;						//Funcion de devolver color de la clase Peon
	bool getMemoria() override;
	Tipo_pieza getTipo() override;
};

