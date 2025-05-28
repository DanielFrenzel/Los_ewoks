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

	State comprobarMov(TABLERO& casillas,Casilla& cas1, Casilla& cas2,int peon_doble_avance_fila_anterior,int peon_doble_avance_columna_anterior) override;
	std::vector<Casilla*> movimientosPosibles(const TABLERO& tablero, Casilla& origen) override;
	void dibujar(float x, float y) override;		//Funcion de dibujar de la clase Peon
	char getColor() override;						//Funcion de devolver color de la clase Peon
	bool getMemoria() override;
	void setMemoria(bool val); 
	Tipo_pieza getTipo() override;
};

