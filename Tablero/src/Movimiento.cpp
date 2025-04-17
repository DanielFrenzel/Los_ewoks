#include "Movimiento.h"


void Movimiento::movimiento(Casilla (&cas)[8][8], int fil1, int col1, int fil2, int col2)
{
	int fich = cas[fil1][col1].getficha();
	if (pieza.compMov(cas, fil1, col1, fil2, col2))
	{
		if (fich != 0)
		{
			cas[fil2][col2].setficha(fich, cas[fil1][col1].getcolor());
		}
		cas[fil1][col1].setficha(0, 0);
	}
	

}