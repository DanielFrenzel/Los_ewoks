#include "Coordinador.h"

void Coordinador::MovRaton(int x, int y)
{
	int fil3=0, col3=0;
	if ((x >= 100 || x <= 700) && (y >= 0 || y <= 600))
	{
		for (int i = 0;i < 8;i++)
		{
			if ((x >= 100 + (75 * (i))) && (x <= 100 + (75 * (i + 1))))
			{
				col3 = i;
			}
			if ((y >= 0 + (75 * (i))) && (y <= 0 + (75 * (i + 1))))
			{
				fil3 = (7 - i);
			}
		}
		tablero.seleccion(fil3, col3);
	}
}