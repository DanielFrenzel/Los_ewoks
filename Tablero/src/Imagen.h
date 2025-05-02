#pragma once
#include<string>
#include"ETSIDI.h"

using namespace ETSIDI;
using namespace std;

class Imagen
{
private:
	string nombre;
	float la_x;
	float la_y;
	float tamx;
	float tamy;

public:
	Sprite* crearImagen(const char* nom, float& x, float& y, float& tax, float& tay);
	void liberaImagen(Sprite* s);
};
