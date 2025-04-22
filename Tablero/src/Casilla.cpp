#include "Casilla.h"

Casilla::Casilla()
{

}

Casilla::Casilla(int &f, int &c, int fich, char col)
{
	fila = f;
	columna = c;
	piezas.setficha(fich);
	piezas.setcolor(col);
	piezas.lugar(f, c);

}

void Casilla:: dibuja()
{
	piezas.dibujar();
}

int Casilla::getficha()
{
	return piezas.getficha();
}

void Casilla::setficha(int f, char col)
{
	piezas.setficha(f);
	piezas.setcolor(col);
}

int Casilla::getfila()
{
	return piezas.getfila();
}

int Casilla::getcolumna()
{
	return piezas.getcolumna();
}

char Casilla::getcolor()
{
	return piezas.getcolor();
}

void Casilla::Casilla_seleccionada()
{
	float _x = (piezas.getcolumna() * 8) - 28;
	float _y = (piezas.getfila() * 8) - 28;
	Sprite casilla_seleccionada{ "imagenes/casilla_seleccionada.png",_x,_y,8,8 };
	if (piezas.getficha() != 0)
	{
		casilla_seleccionada.draw();
	}
	
}

bool Casilla::GetMemoriaPeon()
{
	return memoriaPeon;
}

void Casilla::SetMemoriaPeon(bool estado)
{
	memoriaPeon = estado;
}



