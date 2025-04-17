#include "Torre.h"


static bool comer(char color1, char color2)
{
	if (color1 == color2)
		return 0;
	else return 1;
}


bool Torre::ComprobarMov(Casilla casillas[8][8], int fil1, int col1, int fil2, int col2)
{
	if (col1 == col2 && fil1 == fil2) // si se le pulsa en el mismo sitio no se ueve
	{
		return 0;
	}
	else if (col1 == col2)
	{
		int direccion = (fil1 < fil2) ? 1 : -1;  // comprueba si tiene que sumar o restar
		for (int i = fil1 + direccion; i != fil2; i += direccion)
		{
			if (casillas[i][col1].getficha() != 0)
				return 0; 
			
		}
		return comer(casillas[fil1][col1].getcolor(), casillas[fil2][col2].getcolor());

	}
	else if (fil1 == fil2)  
	{
		int direccion = (col1 < col2) ? 1 : -1;  // comprueba si tiene que sumar o restar
		for (int i = col1 + direccion; i != col2; i += direccion)
		{
			if (casillas[fil1][i].getficha() != 0)
				return 0; // obstáculo
		}
		return comer(casillas[fil1][col1].getcolor(), casillas[fil2][col2].getcolor());
	}
	else return 0;
}

