#include "Tablero.h"

Tablero::Tablero()
{
	casilla = new Casilla * [8]; //reservamos memoria
	for (int i = 0; i < 8; i++)
		casilla[i] = new Casilla[8];
	for (int i = 0;i < 8;i++)
	{
		for (int j = 0;j < 8;j++)
		{
			if (i == 0)
			{
				casilla[i][j] = Casilla(i, j, patron1[j], 'B');
			}
			else if (i == 1)
			{
				casilla[i][j] = Casilla(i, j, patron2[j], 'B');
				casilla[i][j].SetMemoriaPeon(0);
			}
			else if (i == 6)
			{
				casilla[i][j] = Casilla(i, j, patron2[j], 'N');
				casilla[i][j].SetMemoriaPeon(0);
			}
			else if (i == 7)
			{
				casilla[i][j] = Casilla(i, j, patron1[j], 'N');
			}
			else
			{
				casilla[i][j] = Casilla(i, j, 0, 0);
			}
		}
	}

}
void Tablero::dibuja()
{
	for (int i = 0;i < 8;i++)//Imprime piezas blancas
	{
		for (int j = 0;j < 8;j++)
		{
			casilla[i][j].dibuja();
		}
	}
	
	casilla[f][c].Casilla_seleccionada();

	tablero.draw();
	
}

void Tablero::mueve( int fil1, int col1, int fil2, int col2)
{
	if (not (fil1==fil2 && col1==col2))
	{
		mover.movimiento(casilla, fil1, col1, fil2, col2);
	}

}

void Tablero::seleccion(int f1, int c1)
{
	f = f1;
	c = c1;
}


