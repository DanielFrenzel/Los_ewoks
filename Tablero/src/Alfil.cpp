#include "Alfil.h"


Alfil::Alfil(char col)
{
	color = col;
}

bool Alfil::comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2)
{
	int filaOrigen = cas1.getfila();
	int filaDestino = cas2.getfila();

	int columnaOrigen = cas1.getcolumna();
	int columnaDestino = cas2.getcolumna();

	auto fichaDestino = casillas[cas2.getfila()][cas2.getcolumna()].getficha();

	char colorDestino = casillas[cas2.getfila()][cas2.getcolumna()].getcolor();

	int direccionFil = (filaOrigen < filaDestino) ? 1 : -1;
	int direccionCol = (columnaOrigen < columnaDestino) ? 1 : -1;

	if (abs(filaOrigen - filaDestino) == abs(columnaOrigen - columnaDestino))
	{
		int i = filaOrigen + direccionFil;
		int j = columnaOrigen + direccionCol;

		while (i != filaDestino && j != columnaDestino)
		{
			if (casillas[i][j].getficha() != 0)
				return false;
			i += direccionFil;
			j += direccionCol;
		}
		if (fichaDestino == 0)
		{
			return 1;
		}
		if (color != colorDestino)
		{
			return 1;
		}
		else
			return 0;

	}
	return 0;
}

void Alfil::dibujar(float x, float y)
{
	if (color == 'B')
	{
		Sprite* alfilB = Imagen::crearImagen("imagenes/Yoda.png", x, y, tam, tam);
	}
	if (color == 'N')
	{
		Sprite* alfilN = Imagen::crearImagen("imagenes/Doku_1.png", x, y, tam9, tam10);
	}
}


char Alfil::getColor()
{
	return color;
}