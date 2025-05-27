#pragma once
//Hacemos include de la casilla (para movernos sin saltar piezas) y de las Piezas
#include"Casilla.h"
#include"Piezas.h"
#include"Peon.h"
#include"Tablero.h"
#include<array>


using TABLERO = array<array<Casilla, 8>, 8>;

class Movimiento
{
private:
	static Piezas* pieza;													/*Creamos objeto de piezas(static) ya que usamos
																					funciones est�ticas*/

public:
	Movimiento();															//Constructor

	static void mover(TABLERO& casillas, Casilla& cas1, Casilla& cas2);		//Funcion de movimiento de piezas
	static std::vector<std::pair<Casilla*, Casilla*>> obtenerTodasLasCapturasPosibles(const TABLERO& tablero, char colorQueDebeMover);
	static std::vector<Casilla*> obtenerMovimientosFiltrados(const TABLERO& tablero, Casilla& origen, char turnoActual);
	static bool esCapturaAlPaso(const TABLERO& casillas, Casilla& origen, Casilla& destino); //M�todo para gestionar la captura al paso de pe�n pasante
	static void setPieza(Piezas* p);										//Setter
};
