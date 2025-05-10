#include "Peon.h"

Peon::Peon(char col)
{
	//Inicializamos los atributos

	color = col;
	memoria = true;
	capturaPaso = false;
	tipo = PEON;
}

State Peon::comprobarMov(TABLERO& casillas, Casilla& cas1, Casilla& cas2)
{
	int mov = (memoria == true) ? 2 : 1;						//Si la memoria es true el movimiento es de 2

	char colorDestino = cas2.getcolor();

	int filaOrigen = cas1.getfila();
	int filaDestino = cas2.getfila();

	int columnaOrigen = cas1.getcolumna();
	int columnaDestino = cas2.getcolumna();

	auto fichaOrigen = casillas[cas1.getfila()][cas1.getcolumna()].getficha();
	auto fichaDestino = casillas[cas2.getfila()][cas2.getcolumna()].getficha();

	int filaValida1 = casillas[cas1.getfila()][cas1.getcolumna()].getfila();
	int filaValida2 = casillas[cas1.getfila()][cas2.getcolumna()].getfila();

	bool memo = casillas[cas1.getfila()][cas2.getcolumna()].getMemoria();

	Tipo_pieza fichaPaso = casillas[cas1.getfila()][cas1.getcolumna()].getTipo();

	capturaPaso = false;

	if (filaDestino == filaOrigen + 2 || filaDestino == filaOrigen - 2)
	{
		capturaPaso = true;
	}

	if (color == 'B')//Para fichas blancas
	{
		if (filaDestino == (filaOrigen + 1) && (abs(columnaDestino - columnaOrigen) == 1)	//Condicion de peon pasante
			&& (fichaDestino == 0) && (memo == true) && (fichaPaso == PEON) && (filaValida2 == 4))
		{
			return PASANTE;
		}

		if (((filaDestino == (filaOrigen + 1)) || (filaDestino == (filaOrigen + mov))) //Condicion de movimiento
			&& (columnaOrigen == columnaDestino) && (fichaDestino == 0))
		{
			memoria = false; //Ponemos la memoria a false despues del primer movimiento
			return NORMAL;
		}

		if (filaDestino == (filaOrigen + 1) && (abs(columnaDestino - columnaOrigen) == 1) //Condicion de comer
			&& (fichaDestino != 0) && (colorDestino == 'N'))
		{
			return NORMAL;
		}

		else
		{
			return INVALIDO;
		}

	}
	if (color == 'N')//Para fichas negras
	{
		if (filaDestino == (filaOrigen - 1) && (abs(columnaDestino - columnaOrigen) == 1)	//Condicion de peon pasante
			&& (fichaDestino == 0) && (memo == true) && (fichaPaso == PEON) && (filaValida2 == 3))
		{
			return PASANTE;
		}

		if (((filaDestino == (filaOrigen - 1)) || (filaDestino == (filaOrigen - mov))) //Condicion de movimiento
			&& (columnaOrigen == columnaDestino) && (fichaDestino == 0))
		{
			memoria = false; //Ponemos la memoria a false despues del primer movimiento
			return NORMAL;
		}

		if (filaDestino == (filaOrigen - 1) && (abs(columnaDestino - columnaOrigen) == 1) //Condicion de comer
			&& (fichaDestino != 0) && (colorDestino == 'B'))
		{
			return NORMAL;
		}

		else
		{
			return INVALIDO;
		}
	}
}

void Peon::dibujar(float x, float y)
{
	//Dibujamos los peones

	if (color == 'B')
	{
		Sprite* peonB = Imagen::crearImagen("imagenes/R2D2.png", x, y, tam, tam);
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

bool Peon::getMemoria()
{
	return capturaPaso;
}

Tipo_pieza Peon::getTipo()
{
	return tipo;
}