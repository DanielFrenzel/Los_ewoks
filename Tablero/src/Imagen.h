#pragma once

#include"ETSIDI.h"

using namespace ETSIDI;

class Imagen
{
private:
	static Sprite* nombreImagen;							/*Creamos objeto Sprite y lo hacemos static*/
public:
	static Sprite* crearImagen(const char* nom,				//Creamos la imagen
		float& x, float& y, float& tam_x, float& tam_y);
	~Imagen()												//Destruimos la imagen con delete
	{
		if (nombreImagen != nullptr)
		{
			delete nombreImagen;
		}
	}
};
