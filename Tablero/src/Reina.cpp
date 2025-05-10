#include "Reina.h"

Reina::Reina(char col)
{
	color = col;
}

State Reina::comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2)
{
	Alfil alfilTemp(color);  // Puedes pasar color si lo necesitas
	Torre torreTemp(color);

	State movimiento = alfilTemp.comprobarMov(casillas, cas1, cas2);
	if (movimiento != INVALIDO)
		return movimiento;
	return (torreTemp.comprobarMov(casillas, cas1, cas2));
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