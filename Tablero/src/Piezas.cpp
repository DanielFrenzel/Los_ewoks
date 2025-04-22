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
			//Sprite peonB{ "imagenes/R2D2.png",_x,_y,5,5 };
			//peonB.draw();
			Sprite* peonB = imagen.crearImagen("imagenes/R2D2.png", _x, _y, tam, tam5);
			imagen.liberaImagen(peonB);
			//imagen.muestraImagen();
		}
		else if (color == 'N')
		{
			Sprite* peonN = imagen.crearImagen("imagenes/Droide.png", _x, _y, tam2, tam3);
			imagen.liberaImagen(peonN);
		}
		break;
	}
	case 2://Caballo
	{
		if (color == 'B')
		{
			Sprite* caballoB = imagen.crearImagen("imagenes/Windu.png", _x, _y, tam, tam);
			imagen.liberaImagen(caballoB);
		}
		else if (color == 'N')
		{
			Sprite* caballoN = imagen.crearImagen("imagenes/BobaFet.png", _x, _y, tam, tam);
			imagen.liberaImagen(caballoN);
		}
		break;
	}

	case 1://Torre
	{
		if (color == 'B')
		{
			Sprite* torreB = imagen.crearImagen("imagenes/Chewy.png", _x, _y, tam, tam);
			imagen.liberaImagen(torreB);
		}
		else if (color == 'N')
		{
			Sprite* torreN = imagen.crearImagen("imagenes/Superdroide.png", _x, _y, tam7, tam8);
			imagen.liberaImagen(torreN);
		}
		break;
	}
	case 3://Alfil
	{
		if (color == 'B')
		{
			Sprite* alfilB = imagen.crearImagen("imagenes/Yoda.png", _x, _y, tam, tam);
			imagen.liberaImagen(alfilB);
		}
		else if (color == 'N')
		{
			Sprite* alfilN = imagen.crearImagen("imagenes/Doku_1.png", _x, _y, tam9, tam10);
			imagen.liberaImagen(alfilN);
		}
		break;
	}
	case 4://Rey
	{
		if (color == 'B')
		{
			Sprite* reyB = imagen.crearImagen("imagenes/Obiwan.png", _x, _y, tam, tam);
			imagen.liberaImagen(reyB);
		}
		else if (color == 'N')
		{
			Sprite* reyN = imagen.crearImagen("imagenes/Palpatine.png", _x, _y, tam, tam);
			imagen.liberaImagen(reyN);
		}
		break;
	}
	case 5://Reina
	{
		if (color == 'B')
		{
			Sprite* reinaB = imagen.crearImagen("imagenes/Rey.png", _x, _y, tam, tam);
			imagen.liberaImagen(reinaB);
		}
		else if (color == 'N')
		{
			Sprite* reinaN = imagen.crearImagen("imagenes/Vader_or.png", _x, _y, tam5, tam6);
			imagen.liberaImagen(reinaN);
		}
		break;
	}
	}

}



