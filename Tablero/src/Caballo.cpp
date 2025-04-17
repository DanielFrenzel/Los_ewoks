#include "Caballo.h"
#include <math.h>

using namespace std;

bool Caballo::ComprobarMov(Casilla casillas[8][8], int fil1, int col1, int fil2, int col2)
{
	if (((fabs(fil1 - fil2) == 2 && fabs(col1 - col2) == 1) || (fabs(col1 - col2) == 2 && fabs(fil1 - fil2) == 1)))
	{
		if (casillas[fil2][col2].getcolor() == 0 || casillas[fil1][col1].getcolor() != casillas[fil2][col2].getcolor())
			return 1;
		else return 0;
		
	}
	return 0;
}
