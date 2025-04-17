#include "Peon.h"
#include "Casilla.h"
void Peon::dibuja()
{
	
	//peon.draw();
	
}

bool Peon::ComprobarMov(Casilla (casillas)[8][8], int fil1, int col1, int fil2, int col2)
{
	color = casillas[fil1][col1].getcolor();
	if (color == 'B')
	{
		if (fil2 == (fil1 + 1) && col1 == col2 && casillas[fil2][col2].getficha() == 0)
		{
			return 1;
		}
		else if (fil2 == fil1 + 1 && std::abs(col2 - col1) == 1 && casillas[fil2][col2].getficha() != 0 && casillas[fil2][col2].getcolor() != color)
		{
			return 1;
		}
		else
		{
		return 0;
		}
	}
	if (color == 'N')
	{
		if (fil2 == (fil1 - 1) && col1 == col2 && casillas[fil2][col2].getficha() == 0 )
		{
			return 1;
		}
		else if (fil2 == fil1 - 1 && std::abs(col2 - col1) == 1 && casillas[fil2][col2].getficha() != 0 && casillas[fil2][col2].getcolor() != color)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	
}


