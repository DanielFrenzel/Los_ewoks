#include "Tablero.h"

Tablero::Tablero()																//Constructor
{
	//Inicializamos los atributos
	f = 0;
	c = 0;

	x = 0;
	y = 0;
	tam_x = 64;
	tam_y = 64;


	//Creamos doble bucle for para meter las fichas en la matriz
	for (int i = 0;i < 8;i++)
	{
		for (int j = 0;j < 8;j++)
		{
			casilla[i][j].setPosicion(i, j);									//Pasamos la posicion de cada casilla a la propia casilla

			if (i == 0)															//Primera fila de blancas
			{
				if (j == 0 || j == 7)//Torre
				{
					casilla[i][j].setficha(new Torre('B'));
					casilla[i][j].setficha(new Torre('B'));
				}

				else if (j == 1 || j == 6)//Caballo
				{
					casilla[i][j].setficha(new Caballo('B'));
					casilla[i][j].setficha(new Caballo('B'));
				}

				else if (j == 2 || j == 5)//Alfil
				{
					casilla[i][j].setficha(new Alfil('B'));
					casilla[i][j].setficha(new Alfil('B'));
				}

				else if (j == 3)//Reina
				{
					casilla[i][j].setficha(new Reina('B'));
					casilla[i][j].setficha(new Reina('B'));
				}

				else if (j == 4)//Rey
				{
					casilla[i][j].setficha(new Rey('B'));
					casilla[i][j].setficha(new Rey('B'));
				}
			}

			else if (i == 1)													//Segunda fila de blancas
			{
				casilla[i][j].setficha(new Peon('B'));
			}

			else if (i == 6)													//Segunda fila de negras
			{
				casilla[i][j].setficha(new Peon('N'));
			}

			else if (i == 7)													//Primera fila de negras
			{
				if (j == 0 || j == 7)//Torre
				{
					casilla[i][j].setficha(new Torre('N'));
					casilla[i][j].setficha(new Torre('N'));
				}

				if (j == 1 || j == 6)//Caballo
				{
					casilla[i][j].setficha(new Caballo('N'));
					casilla[i][j].setficha(new Caballo('N'));
				}

				if (j == 2 || j == 5)//Alfil
				{
					casilla[i][j].setficha(new Alfil('N'));
					casilla[i][j].setficha(new Alfil('N'));
				}

				if (j == 3)//Reina
				{
					casilla[i][j].setficha(new Reina('N'));
					casilla[i][j].setficha(new Reina('N'));
				}

				if (j == 4)//Rey
				{
					casilla[i][j].setficha(new Rey('N'));
					casilla[i][j].setficha(new Rey('N'));
				}
			}

			else//Nada
			{
				casilla[i][j].setficha(nullptr);
			}
		}
	}

}

void Tablero::dibuja()															//Dibujamos las piezas y el tablero
{
	for (int i = 0;i < 8;i++)													//Imprime piezas
	{
		for (int j = 0;j < 8;j++)
		{
			casilla[i][j].dibuja();
		}
	}

	casilla[f][c].Casilla_seleccionada();										//Imprime casilla seleccionada

	tablero.draw();
	fondo.draw();

}

void Tablero::mueve(int fil1, int col1, int fil2, int col2)					//Movimiento de las piezas
{
	Movimiento::setPieza(casilla[fil1][col1].getficha());						/*Pasamos la pieza seleccionada a la clase Movimiento
																					(para que sepa la pieza seleccionada)*/

	if (not (fil1 == fil2 && col1 == col2))											//Si la fila y la columna de incio y fin son distnitas
	{
		Movimiento::mover(casilla, casilla[fil1][col1], casilla[fil2][col2]);	/*Pasamos el tablero entero y las dos casillas de incio
																					y fin a la clase Movimiento*/
	}

}

void Tablero::seleccion(int f1, int c1)											//Funcion de seleccion de la casilla(meter al coordinador)
{
	f = f1;
	c = c1;
}
