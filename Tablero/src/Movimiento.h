#pragma once
//Hacemos include de la casilla (para movernos sin saltar piezas) y de las Piezas
#include"Casilla.h"
#include"Piezas.h"
#include<array>

using TABLERO = array<array<Casilla, 8>, 8>;

class Movimiento
{
private:
	static Piezas *pieza;													/*Creamos objeto de piezas(static) ya que usamos
																					funciones estáticas*/

public:
	Movimiento();															//Constructor

	static void mover(TABLERO& casillas, Casilla& cas1, Casilla& cas2);		//Funcion de movimiento de piezas

	static void setPieza(Piezas* p);										//Setter
};

