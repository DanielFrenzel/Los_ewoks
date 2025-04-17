#include "MovPiezas.h"

bool MovPiezas::compMov(Casilla casilla[8][8], int fil1, int col1, int fil2, int col2)
{
	ficha = casilla[fil1][col1].getficha();
	switch(ficha)
	{
	case 6:
		return peon.ComprobarMov(casilla, fil1, col1, fil2, col2);
	case 5: 
		return alfil.ComprobarMov(casilla, fil1, col1, fil2, col2) || torre.ComprobarMov(casilla, fil1, col1, fil2, col2);
	case 4:
		return rey.ComprobarMov(casilla, fil1, col1, fil2, col2);
	case 3:
		return alfil.ComprobarMov(casilla, fil1, col1, fil2, col2);
	case 2:
		return caballo.ComprobarMov(casilla, fil1, col1, fil2, col2);
	case 1:
		return torre.ComprobarMov(casilla, fil1, col1, fil2, col2);
	}
	
}