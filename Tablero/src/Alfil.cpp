#include "Alfil.h"
#include <math.h>

bool Alfil::ComprobarMov(Casilla** casillas, int fil1, int col1, int fil2, int col2)
{
	int direccionFil = (fil1 < fil2) ? 1 : -1;
	int direccionCol = (col1 < col2) ? 1 : -1;
	if (fabs(fil1 - fil2) == fabs(col1 - col2))
	{
		int i = fil1 + direccionFil;
		int j = col1 + direccionCol;

		while (i != fil2 && j != col2)
		{
			if (casillas[i][j].getficha() != 0)
				return false;
			i += direccionFil;
			j += direccionCol;
		}
		if (casillas[fil2][col2].getficha() == 0)
		{
			return 1;
		}
		else if (casillas[fil1][col1].getcolor() != casillas[fil2][col2].getcolor())
		{
			return 1;
		}
		else
			return 0;
		
	}
	return 0;
}