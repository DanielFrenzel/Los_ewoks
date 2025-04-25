#pragma once
#include<string>
#include"ETSIDI.h"
#include"Boton.h"
#include "vector"

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
	vector <Boton*> botones;
public:
	Sprite* crearImagen(const char* nom, float& x, float& y, float& tax, float& tay);
	void liberaImagen(Sprite* s);
	void add_boton(Boton* entrada);
	void eliminar_boton();
};

