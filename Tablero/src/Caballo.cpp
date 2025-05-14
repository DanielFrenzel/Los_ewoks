#include "Caballo.h"

Caballo::Caballo(char col)
{
	color = col;
}

State Caballo::comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2)
{
	int filaOrigen = cas1.getfila();
	int filaDestino = cas2.getfila();

	int columnaOrigen = cas1.getcolumna();
	int columnaDestino = cas2.getcolumna();

	char colorDestino = casillas[cas2.getfila()][cas2.getcolumna()].getcolor();

	if (((abs(filaOrigen - filaDestino) == 2 && abs(columnaOrigen - columnaDestino) == 1)
		|| (abs(columnaOrigen - columnaDestino) == 2 && abs(filaOrigen - filaDestino) == 1)))
	{
		if (colorDestino == 0 || color != colorDestino) return NORMAL;
		else return INVALIDO;

	}
	return INVALIDO;
}

void Caballo::dibujar(float x, float y)
{
	if (color == 'B')
	{
		Sprite* caballoB = Imagen::crearImagen("imagenes/Windu.png", x, y, tam, tam);
	}
	if (color == 'N')
	{
		Sprite* caballoN = Imagen::crearImagen("imagenes/BobaFet.png", x, y, tam, tam);
	}
}

char Caballo::getColor()
{
	return color;
}

Tipo_pieza Caballo::getTipo()
{
	return tipo;
}