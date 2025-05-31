#pragma once
//Hacemos include de la casilla (para movernos sin saltar piezas) y de las Piezas
#include"Casilla.h"
#include"Piezas.h"
#include"Tablero.h"
#include<array>


using TABLERO = array<array<Casilla, 8>, 8>;

class Movimiento
{
private:
	static Piezas* pieza;													/*Creamos objeto de piezas(static) ya que usamos
																					funciones estáticas*/

public:
	Movimiento();															//Constructor
	static std::vector<std::pair<Casilla*, Casilla*>> obtenerTodasLasCapturasPosibles(const TABLERO& tablero, char colorQueDebeMover,int peon_doble_avance_fila_anterior, int peon_doble_avance_columna_anterior);
	static std::vector<Casilla*> obtenerMovimientosFiltrados(const TABLERO& tablero, Casilla& origen, char turnoActual,int peon_doble_avance_fila_anterior, int peon_doble_avance_columna_anterior);
	static void setPieza(Piezas* p);										//Setter
};
