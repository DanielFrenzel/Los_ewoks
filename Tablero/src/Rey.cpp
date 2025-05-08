#include "Rey.h"

Rey::Rey(char col)
{
	color = col;
}

bool Rey::comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2)
{
	int filaOrigen = cas1.getfila();
	int filaDestino = cas2.getfila();

	int columnaOrigen = cas1.getcolumna();
	int columnaDestino = cas2.getcolumna();

	char colorDestino = casillas[cas2.getfila()][cas2.getcolumna()].getcolor();

	if ((abs(filaOrigen - filaDestino) == 1 || abs(columnaOrigen - columnaDestino) == 1) && colorDestino != color)
	{
		return 1;
	}
	else return 0;
}

void Rey::dibujar(float x, float y)
{
	if (color == 'B')
	{
		Sprite* reyB = Imagen::crearImagen("imagenes/Obiwan.png", x, y, tam, tam);
	}
	else if (color == 'N')
	{
		Sprite* reyN = Imagen::crearImagen("imagenes/Palpatine.png", x, y, tam, tam);
	}
}

char Rey::getColor()
{
	return color;
}