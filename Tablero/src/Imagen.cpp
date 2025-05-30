#include "Imagen.h"

vector<Sprite*> Imagen::sprites;

Sprite* Imagen::crearImagen(const char* nom, float& x, float& y, float& tam_x, float& tam_y)
{
	Sprite* nuevoSprite = new Sprite{ nom,x,y,tam_x,tam_y };	//Creamos nuevo objeto
	sprites.push_back(nuevoSprite);
	nuevoSprite->draw();								//Lo dibujamos
	return nuevoSprite;								//Devuelvo el puntero
}

void Imagen::eliminarImagenes()
{
	for (Sprite* s : sprites) {
		delete s; // Eliminamos cada Sprite
	}
	sprites.clear();  // Limpiamos el vector
}