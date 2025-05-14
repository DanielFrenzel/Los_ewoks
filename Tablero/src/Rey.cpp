#include "Rey.h"

Rey::Rey(char col)
{
	color = col;
}

State Rey::comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2)
{
	int filaOrigen = cas1.getfila();
	int filaDestino = cas2.getfila();

	int columnaOrigen = cas1.getcolumna();
	int columnaDestino = cas2.getcolumna();

	int df = abs(filaOrigen - filaDestino);
	int dc = abs(columnaOrigen - columnaDestino);

	char colorDestino = casillas[cas2.getfila()][cas2.getcolumna()].getcolor();

	if (((df <= 1 && dc <= 1) && !(df == 0 && dc == 0)) && colorDestino != color)
	{
		return NORMAL;
	}
	else return INVALIDO;
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

Tipo_pieza Rey::getTipo()
{
	return tipo;
}