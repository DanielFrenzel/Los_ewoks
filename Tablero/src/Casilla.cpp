#include "Casilla.h"

Casilla::Casilla()
{
	//Iniciazliamos los atributos

	fila = 0;
	columna = 0;
	pieza = nullptr;
	esta_resaltada = false; // Inicializar

}

void Casilla::dibuja()
{
	//Dibujamos las piezas

	//Coordenadas en x e y en la pantallas

	float x = (columna * 4) - 14;
	float y = (fila * 4.75) - 16.5;

	if (pieza != nullptr)
	{
		pieza->dibujar(x, y);
		if (esta_resaltada) {
			Sprite* sprite_resaltado = Imagen::crearImagen("imagenes/casilla_seleccionada.png", x, y, tam, tam);
		}
	}

}


//-------------------------------------------Getters

Piezas* Casilla::getficha() const
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
	return ' ';
}

bool Casilla::getMemoria()
{
	if (pieza != nullptr)
	{
		return pieza->getMemoria();
	}
	return false;
}

Tipo_pieza Casilla::getTipo()
{
	if (pieza != nullptr)
	{
		return pieza->getTipo();
	}
	return NADA;
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

