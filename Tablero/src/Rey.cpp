#include "Rey.h"
#include <math.h>

using namespace std;

bool Rey::ComprobarMov(Casilla** casillas, int fil1, int col1, int fil2, int col2)
{
	if ((fabs(fil1 - fil2) == 1 || fabs(col1 - col2) == 1) && casillas[fil2][col2].getcolor() != casillas[fil1][col1].getcolor())
	{
		return 1;
	}
	else return 0;
}
