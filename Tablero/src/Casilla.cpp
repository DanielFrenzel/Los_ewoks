#include "Casilla.h"

Casilla::Casilla()
{
	//Iniciazliamos los atributos

	fila = 0;
	columna = 0;
	pieza = nullptr;
}

void Casilla::dibuja()
{
	//Dibujamos las piezas

	//Coordenadas en x e y en la pantallas

	float x = (columna * 5.8) - 20;
	float y = (fila * 5.8) - 20.5;

	if (pieza != nullptr)
	{
		pieza->dibujar(x, y);
	}
}

void Casilla::Casilla_seleccionada()
{
	//Dibujamos la casilla seleccionada

	//float x = (columna * 5.05) - 20.2;
	//float y = (fila * 5.05) + 20.2;
	float x = (columna * 8) - 28;  // Centrado horizontal
	float y = (fila * 8) - 151;
	float tam_x = 6, tam_y = 6;
	//Sprite* casilla_seleccionada = Imagen::crearImagen("imagenes/casilla_seleccionada.png", x, y, tam_x, tam_y);

}

//-------------------------------------------Getters

Piezas* Casilla::getficha()
{
	return pieza;
}

int& Casilla::getfila()
{
	return fila;
}

int& Casilla::getcolumna()
{
	return columna;
}

char Casilla::getcolor()
{
	if (pieza != nullptr)
	{
		return pieza->getColor();
	}
}

//-------------------------------------------Setters

void Casilla::setPosicion(int fil, int col)
{
	fila = fil;
	columna = col;
}

void Casilla::setficha(Piezas* p)
{
	pieza = p;
}


