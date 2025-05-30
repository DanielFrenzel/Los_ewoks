#pragma once

#include"ETSIDI.h"
#include<vector>

using namespace ETSIDI;
using std::vector;

class Imagen
{
private:
	static vector<Sprite*> sprites;							/*Creamos objeto Sprite y lo hacemos static*/
public:
	static Sprite* crearImagen(const char* nom,				//Creamos la imagen
		float& x, float& y, float& tam_x, float& tam_y);
	static void eliminarImagenes();
};
