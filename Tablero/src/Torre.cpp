#include "Torre.h"

Torre::Torre(char col)
{
	color = col;
}

bool Torre::comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2)
{
	int filaOrigen = cas1.getfila();
	int filaDestino = cas2.getfila();

	int columnaOrigen = cas1.getcolumna();
	int columnaDestino = cas2.getcolumna();

	char colorDestino = casillas[cas2.getfila()][cas2.getcolumna()].getcolor();

	if (columnaOrigen == columnaDestino && filaOrigen == filaDestino) // si se le pulsa en el mismo sitio no se ueve
	{
		return 0;
	}
	if (columnaOrigen == columnaDestino)
	{
		int direccion = (filaOrigen < filaDestino) ? 1 : -1;  // comprueba si tiene que sumar o restar
		for (int i = (filaOrigen + direccion); i != filaDestino; i += direccion)
		{
			if (casillas[i][columnaOrigen].getficha() != 0)
				return 0;

		}
		return comer(color, colorDestino);

	}
	if (filaOrigen == filaDestino)
	{
		int direccion = (columnaOrigen < columnaDestino) ? 1 : -1;  // comprueba si tiene que sumar o restar
		for (int i = (columnaOrigen + direccion); i != columnaDestino; i += direccion)
		{
			if (casillas[filaOrigen][i].getficha() != 0)
				return 0; // obstáculo
		}
		return comer(color, colorDestino);
	}
	else return 0;
}

void Torre::dibujar(float x, float y)
{
	if (color == 'B')
	{
		Sprite* torreB = Imagen::crearImagen("imagenes/Chewy.png", x, y, tam, tam);
	}
	if (color == 'N')
	{
		Sprite* torreN = Imagen::crearImagen("imagenes/Superdroide.png", x, y, tam7, tam8);
	}
}

char Torre::getColor()
{
	return color;
}