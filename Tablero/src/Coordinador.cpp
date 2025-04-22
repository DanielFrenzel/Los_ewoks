#include "Coordinador.h"

void Coordinador::setTablero(Tablero* t)
{
	tablero = t;
}

void Coordinador::MovRaton(int x, int y)  //Indica que casilla se ha pulsado según 
{
	int fil3 = 0, col3 = 0;
	if ((x >= 100 || x <= 700) && (y >= 0 || y <= 600))
	{
		for (int i = 0; i < 8; i++)
		{
			if ((x >= 100 + (75 * i)) && (x <= 100 + (75 * (i + 1))))
			{
				col3 = i;
			}
			if ((y >= 0 + (75 * i)) && (y <= 0 + (75 * (i + 1))))
			{
				fil3 = (7 - i);
			}
		}
		if(tablero)
		tablero->seleccion(fil3, col3);
	}
}

void Coordinador::movimiento(int fil1, int col1, int fil2, int col2)  //mueve la ficha de la selección 1 a la 2
{
	char color = (turno == 0) ? 'B' : 'N';

	if (fil1 == fil2 && col1 == col2)
		return;

	if (compMov(fil1, col1, fil2, col2) && tablero->getCasillas()[fil1][col1].getcolor() == color)
	{
		if (tablero->getCasillas()[fil1][col1].getficha() != 0)
		{
			tablero->getCasillas()[fil2][col2].setficha(tablero->getCasillas()[fil1][col1].getficha() , tablero->getCasillas()[fil1][col1].getcolor());
			tablero->getCasillas()[fil1][col1].setficha(0, 0);

			// Actualiza selección gráfica
			tablero->seleccion(fil2, col2);
			turno = not(turno);
		}
	}
}

bool Coordinador::compMov(int fil1, int col1, int fil2, int col2) //comprueba si se puede mover
{
	switch (tablero->getCasillas()[fil1][col1].getficha())
	{
	case 6:
		return peon.ComprobarMov(tablero->getCasillas() , fil1, col1, fil2, col2);
	case 5:
		return alfil.ComprobarMov(tablero->getCasillas(), fil1, col1, fil2, col2) || torre.ComprobarMov(tablero->getCasillas(), fil1, col1, fil2, col2);
	case 4:
		return rey.ComprobarMov(tablero->getCasillas(), fil1, col1, fil2, col2);
	case 3:
		return alfil.ComprobarMov(tablero->getCasillas(), fil1, col1, fil2, col2);
	case 2:
		return caballo.ComprobarMov(tablero->getCasillas(), fil1, col1, fil2, col2);
	case 1:
		return torre.ComprobarMov(tablero->getCasillas(), fil1, col1, fil2, col2);
	default:
		return false;
	}
}