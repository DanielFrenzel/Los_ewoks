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
	// Coordenadas en x e y en la pantalla
	float x = (columna * 4) - 14;
	float y = (fila * 4.75) - 16.5;

	// Dibuja la pieza si existe
	if (pieza != nullptr)
	{
		pieza->dibujar(x, y);
	}
	// Resaltado si la casilla es parte de los movimientos posibles de la pieza seleccionada
	if (esta_resaltada) {
		// Indicación de los movimientos posibles y la casilla de origen seleccionada
		Sprite* sprite_mov_posible = Imagen::crearImagen("imagenes/casilla_seleccionada.png", x, y, tam, tam);
		/*if (sprite_mov_posible) {
			sprite_mov_posible->draw();
		}*/
	}
	//  Resaltado de mouse-over (solo si no está ya resaltada como movimiento posible/seleccionada)
	else if (esta_resaltada_mouse_over) {
		// sprite para el efecto de pasar el ratón por encima
		Sprite* sprite_mouse_over = Imagen::crearImagen("imagenes/casilla_de_paso.png", x, y, tam, tam); 
		/*if (sprite_mouse_over) {
			sprite_mouse_over->draw();
			
		}*/
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

bool Casilla::getMemoria() const
{
	if (pieza != nullptr)
	{
		return pieza->getMemoria();
	}
	return false;
}

Tipo_pieza Casilla::getTipo() const
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

