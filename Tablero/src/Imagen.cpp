#include "Imagen.h"

Sprite* Imagen::nombreImagen = nullptr;

Sprite* Imagen::crearImagen(const char* nom, float& x, float& y, float& tam_x, float& tam_y)
{
	nombreImagen = new Sprite{ nom,x,y,tam_x,tam_y };	//Creamos nuevo objeto
	nombreImagen->draw();								//Lo dibujamos
	return nombreImagen;								//Devuelvo el puntero
}