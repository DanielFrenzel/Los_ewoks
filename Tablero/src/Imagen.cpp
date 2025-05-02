#include "Imagen.h"
Sprite* Imagen::crearImagen(const char* nom, float& x, float& y, float& tax, float& tay)
{
	Sprite* s = new Sprite{ nom,x,y,tax,tay };
	s->draw();
	return s;//devuelvo un puntero
}

void Imagen::liberaImagen(Sprite* s)
{
	if (s != nullptr)
	{
		delete s;
	}
}