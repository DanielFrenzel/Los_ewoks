#include "Peon.h"

Peon::Peon(char col)
{
	//Inicializamos los atributos

	color = col;
	memoria = true;
	//capturaPaso = false;
}

bool Peon::comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2)
{
	int mov = (memoria == true) ? 2 : 1;						//Si la memoria es true el movimiento es de 2

	char colorDestino = cas2.getcolor();
	int filaOrigen = cas1.getfila();
	int filaDestino = cas2.getfila();

	int columnaOrigen = cas1.getcolumna();
	int columnaDestino = cas2.getcolumna();

	auto fichaDestino = casillas[cas2.getfila()][cas2.getcolumna()].getficha();
	auto fichaPaso = casillas[cas1.getfila()][cas2.getcolumna()].getficha();

	//Peon* peonPaso = dynamic_cast<Peon*>(fichaPaso);//Necesario para que  fichaPaso sepa si contiene un peon

	if (color == 'B')//Para fichas blancas
	{
		if ((filaDestino == (filaOrigen + mov) || (filaDestino == (filaOrigen + 1))) //Condicion de movimiento
			&& (columnaOrigen == columnaDestino) && (fichaDestino == 0))
		{
			memoria = false;									//Ponemos la memoria a false despues del primer movimiento
			/*if (mov == 2)
			{
				capturaPaso = true;
			}*/
			return 1;
		}

		if (filaDestino == (filaOrigen + 1) && (abs(columnaDestino - columnaOrigen) == 1) //Condicion de comer
			&& (fichaDestino != 0) && (colorDestino == 'N'))
		{
			return 1;
		}

		/*if (filaDestino == (filaOrigen + 1) && (abs(columnaDestino - columnaOrigen) == 1) && (ficha == 0) && (fichaPaso != nullptr))
		{
			if (capturaPaso==true)
			{
				return 1;
			}
			if (capturaPaso == false)
			{
				return 0;
			}
		}*/

		else
		{
			return 0;
		}
	}
	if (color == 'N')//Para fichas negras
	{
		if ((filaDestino == (filaOrigen - mov) || filaDestino == (filaOrigen - 1))
			&& (columnaOrigen == columnaDestino) && (fichaDestino == 0))
		{
			memoria = false;
			return 1;
		}

		if (filaDestino == (filaOrigen - 1) && abs(columnaDestino - columnaOrigen) == 1
			&& (fichaDestino != 0) && (colorDestino == 'B'))
		{
			return 1;
		}

		/*if (filaDestino == (filaOrigen - 1) && (abs(columnaDestino - columnaOrigen) == 1) && (ficha == 0) && (fichaPaso != nullptr))
		{
			if (capturaPaso == true)
			{
				return 1;
			}
			if (capturaPaso == false)
			{
				return 0;
			}
		}*/

		else
		{
			return 0;
		}
	}
}

void Peon::dibujar(float x, float y)
{
	//Dibujamos los peones

	if (color == 'B')
	{
		Sprite* peonB = Imagen::crearImagen("imagenes/R2D2.png", x, y, tam, tam5);
	}
	if (color == 'N')
	{
		Sprite* peonN = Imagen::crearImagen("imagenes/Droide.png", x, y, tam2, tam3);
	}
}

//-------------------------------------------Getter

char Peon::getColor()
{
	return color;
}