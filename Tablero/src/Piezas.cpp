#include "Piezas.h"

void Piezas::lugar(int f, int c)
{
	fila = f;
	columna = c;
	_x = (c * 8) - 28;
	_y = (f * 8) - 28;
}

void Piezas::setficha(int f)
{
	ficha = f;
}

void Piezas::setcolor(char col)
{
	color = col;
}

char Piezas::getcolor()
{
	return color;
}

int Piezas::getficha()
{
	return ficha;
}

int Piezas::getfila()
{
	return fila;
}

int Piezas::getcolumna()
{
	return columna;
}

void Piezas::dibujar()
{

	switch (ficha)
	{
	case 6://Peon
	{
		if (color == 'B')
		{
			Sprite peonB{ "imagenes/WhitePawn.png",_x,_y,5,5 };
			peonB.draw();
		}
		else if (color == 'N')
		{
			Sprite peonN{ "imagenes/BlackPawn.png",_x,_y,5,5 };
			peonN.draw();
		}
		break;
	}
	case 2://Caballo
	{
		if (color == 'B')
		{
			caballoB = Sprite{ "imagenes/WhiteKnight.png", _x, _y, 5, 5 };
			caballoB.draw();
		}
		else if (color == 'N')
		{
			caballoN = Sprite{ "imagenes/BlackKnight.png", _x, _y, 5, 5 };
			caballoN.draw();
		}
		break;
	}

	case 1://Torre
	{
		if (color == 'B')
		{
			Sprite torreB{ "imagenes/WhiteRook.png",_x,_y,5,5 };
			torreB.draw();
		}
		else if (color == 'N')
		{
			Sprite torreN{ "imagenes/BlackRook.png",_x,_y,5,5 };
			torreN.draw();
		}
		break;
	}
	case 3://Alfil
	{
		if (color == 'B')
		{
			Sprite alfilB{ "imagenes/WhiteBishop.png",_x,_y,5,5 };
			alfilB.draw();
		}
		else if (color == 'N')
		{
			Sprite alfilN{ "imagenes/BlackBishop.png",_x,_y,5,5 };
			alfilN.draw();
		}
		break;
	}
	case 4://Rey
	{
		if (color == 'B')
		{
			Sprite reyB{ "imagenes/WhiteKing.png",_x,_y,5,5 };
			reyB.draw();
		}
		else if (color == 'N')
		{
			Sprite reyN{ "imagenes/BlackKing.png",_x,_y,5,5 };
			reyN.draw();
		}
		break;
	}
	case 5://Reina
	{
		if (color == 'B')
		{
			Sprite reinaB{ "imagenes/WhiteQueen.png",_x,_y,5,5 };
			reinaB.draw();
		}
		else if (color == 'N')
		{
			Sprite reinaN{ "imagenes/BlackQueen.png",_x,_y,5,5 };
			reinaN.draw();
		}
		break;
	}
	}

}


