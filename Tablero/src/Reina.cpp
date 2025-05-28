#include "Reina.h"

Reina::Reina(char col)
{
	color = col;
}

State Reina::comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2, int peon_doble_avance_fila_anterior, int peon_doble_avance_clomuna_anterior)
{
	Alfil alfilTemp(color);  // Puedes pasar color si lo necesitas
	Torre torreTemp(color);

	State movimiento = alfilTemp.comprobarMov(casillas, cas1, cas2,peon_doble_avance_fila_anterior,peon_doble_avance_clomuna_anterior);
	if (movimiento != INVALIDO)
		return movimiento;
	return (torreTemp.comprobarMov(casillas, cas1, cas2,peon_doble_avance_fila_anterior,peon_doble_avance_clomuna_anterior));
}


std::vector<Casilla*> Reina::movimientosPosibles(const TABLERO& tablero, Casilla& origen) {
	std::vector<Casilla*> posibles_reina;

	// Obtener movimientos posibles de Alfil
	Alfil alfil_temp(this->getColor()); // Se necesita una instancia temporal para llamar a la función
	std::vector<Casilla*> posibles_alfil = alfil_temp.movimientosPosibles(tablero, origen);
	posibles_reina.insert(posibles_reina.end(), posibles_alfil.begin(), posibles_alfil.end());

	// Obtener movimientos posibles de Torre
	Torre torre_temp(this->getColor()); // Se necesita una instancia temporal
	std::vector<Casilla*> posibles_torre = torre_temp.movimientosPosibles(tablero, origen);
	posibles_reina.insert(posibles_reina.end(), posibles_torre.begin(), posibles_torre.end());

	return posibles_reina;
}


void Reina::dibujar(float x, float y)
{
	if (color == 'B')
	{
		Sprite* reinaB = Imagen::crearImagen("imagenes/Rey.png", x, y, tam, tam);
	}
	if (color == 'N')
	{
		Sprite* reinaN = Imagen::crearImagen("imagenes/Vader_or.png", x, y, tam5, tam6);
	}
}

char Reina::getColor()
{
	return color;
}

Tipo_pieza Reina::getTipo()
{
	return tipo;
}